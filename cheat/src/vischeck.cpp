#include <filesystem>
#include <math.hpp>

#include "vischeck.hpp"
#include "kv3-parser.hpp"
#include "utility.hpp"

bool c_vischeck::initialize(const std::string &map_directory_path, const std::string &map_name)
{
    if (!extract_and_decompress_physics_file(map_directory_path, map_name))
    {
        return false;
    }

    parse_physics_data();
    c_utility::delete_directory(m_temp_folder_path);

    return true;
}

bool c_vischeck::is_visible(const math::vec3 &start, const math::vec3 &end)
{
    math::vec3 hit_position0, hit_position1, hit_position2, hit_position3, hit_position4;

    if (ray_trace_mesh(start, end, hit_position0, m_vertices0, m_triangles0) ||
        ray_trace_mesh(start, end, hit_position1, m_vertices1, m_triangles1) ||
        ray_trace_mesh(start, end, hit_position2, m_vertices2, m_triangles2) ||
        ray_trace_mesh(start, end, hit_position3, m_vertices3, m_triangles3) ||
        ray_trace_mesh(start, end, hit_position4, m_vertices4, m_triangles4))
    {
        return false;
    }

    return true;
}

bool c_vischeck::extract_and_decompress_physics_file(const std::string &map_directory_path, const std::string &map_name)
{
    if (!c_utility::create_temp_folder(&m_temp_folder_path))
    {
        return false;
    }

    std::filesystem::path current_path = std::filesystem::current_path();
    const auto decompiler_path = current_path.string() + xors("\\..\\deps\\Decompiler.exe");
    printf("%s\n", decompiler_path.c_str());

    const auto map_vpk_path = map_directory_path + xors("\\") + map_name + xors(".vpk");
    printf("%s\n", map_vpk_path.c_str());

    printf("%s\n", m_temp_folder_path.c_str());

    const auto args = xors("-i \"") + map_vpk_path + xors("\" -o ") + m_temp_folder_path + xors(" -f maps/") + map_name + xors("/world_physics.vphys_c -d");

    if (c_utility::execute_with_arguments(decompiler_path, args))
    {
        return false;
    }

    m_physics_file_path = m_temp_folder_path + xors("\\maps\\") + map_name + xors("\\world_physics.vphys");

    return true;
}

void c_vischeck::parse_physics_data()
{
    std::vector<uint8_t> raw_kv3_data;
    if (!c_utility::read_data_from_file(m_physics_file_path, &raw_kv3_data))
    {
        return;
    }

    std::string raw_kv3_text(raw_kv3_data.begin(), raw_kv3_data.end());

    c_kv3_parser kv3_parser;
    kv3_parser.parse(raw_kv3_text);

    const auto triangles_raw_string0 = kv3_parser.get_value("m_parts[0].m_rnShape.m_meshes[0].m_Mesh.m_Triangles");
    const auto triangles_raw_string1 = kv3_parser.get_value("m_parts[0].m_rnShape.m_meshes[1].m_Mesh.m_Triangles");
    const auto triangles_raw_string2 = kv3_parser.get_value("m_parts[0].m_rnShape.m_meshes[2].m_Mesh.m_Triangles");
    const auto triangles_raw_string3 = kv3_parser.get_value("m_parts[0].m_rnShape.m_meshes[3].m_Mesh.m_Triangles");
    const auto triangles_raw_string4 = kv3_parser.get_value("m_parts[0].m_rnShape.m_meshes[4].m_Mesh.m_Triangles");

    const auto vertices_raw_string0 = kv3_parser.get_value("m_parts[0].m_rnShape.m_meshes[0].m_Mesh.m_Vertices");
    const auto vertices_raw_string1 = kv3_parser.get_value("m_parts[0].m_rnShape.m_meshes[1].m_Mesh.m_Vertices");
    const auto vertices_raw_string2 = kv3_parser.get_value("m_parts[0].m_rnShape.m_meshes[2].m_Mesh.m_Vertices");
    const auto vertices_raw_string3 = kv3_parser.get_value("m_parts[0].m_rnShape.m_meshes[3].m_Mesh.m_Vertices");
    const auto vertices_raw_string4 = kv3_parser.get_value("m_parts[0].m_rnShape.m_meshes[4].m_Mesh.m_Vertices");

    m_triangles0 = kv3_parser.bytes_to_vec<uint32_t>(triangles_raw_string0);
    m_triangles1 = kv3_parser.bytes_to_vec<uint32_t>(triangles_raw_string1);
    m_triangles2 = kv3_parser.bytes_to_vec<uint32_t>(triangles_raw_string2);
    m_triangles3 = kv3_parser.bytes_to_vec<uint32_t>(triangles_raw_string3);
    m_triangles4 = kv3_parser.bytes_to_vec<uint32_t>(triangles_raw_string4);

    m_vertices0 = kv3_parser.bytes_to_vec<math::vec3>(vertices_raw_string0);
    m_vertices1 = kv3_parser.bytes_to_vec<math::vec3>(vertices_raw_string1);
    m_vertices2 = kv3_parser.bytes_to_vec<math::vec3>(vertices_raw_string2);
    m_vertices3 = kv3_parser.bytes_to_vec<math::vec3>(vertices_raw_string3);
    m_vertices4 = kv3_parser.bytes_to_vec<math::vec3>(vertices_raw_string4);
}

const bool c_vischeck::ray_trace_mesh(const math::vec3 &start, const math::vec3 &end, math::vec3 &hit, const std::vector<math::vec3> &vertices, const std::vector<uint32_t> &triangles)
{
    auto point = start;
    auto direction = end - start;
    direction *= 1.0f / direction.length();
    const auto max_distance = end.distance_to(start);

    for (size_t i = 0; i < triangles.size(); i += 3)
    {
        if (i + 2 >= triangles.size())
        {
            continue;
        }

        const auto index0 = triangles[i];
        const auto index1 = triangles[i + 1];
        const auto index2 = triangles[i + 2];

        if (index0 >= vertices.size() || index1 >= vertices.size() || index2 >= vertices.size())
        {
            continue;
        }

        const auto v0 = vertices[index0];
        const auto v1 = vertices[index1];
        const auto v2 = vertices[index2];

        const auto normal = (v1 - v0).cross_product(v2 - v0);
        const auto t = normal.dot_product(v0 - point) / normal.dot_product(direction);

        if (t >= 0.0f && t <= max_distance)
        {
            const math::vec3 t3 = {t, t, t};
            const auto intersection_point = point + t3 * direction;

            const auto f0 = normal.dot_product((v1 - v0).cross_product(intersection_point - v0));
            const auto f1 = normal.dot_product((v2 - v1).cross_product(intersection_point - v1));
            const auto f2 = normal.dot_product((v0 - v2).cross_product(intersection_point - v2));

            if (f0 >= 0.0f && f1 >= 0.0f && f2 >= 0.0f)
            {
                hit = intersection_point;
                return true;
            }
        }
    }

    hit = end;
    return false;
}
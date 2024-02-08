#ifndef VISCHECK_HPP
#define VISCHECK_HPP

#include <vector>
#include <math.hpp>

class c_vischeck
{
public:
    c_vischeck() = default;
    ~c_vischeck() = default;

public:
    bool initialize(const std::string &map_directory_path, const std::string &map_name);
    bool is_visible(const math::vec3 &start, const math::vec3 &end);

private:
    bool extract_and_decompress_physics_file(const std::string &map_directory_path, const std::string &map_name);
    void parse_physics_data();

private:
    const bool ray_trace_mesh(const math::vec3 &start, const math::vec3 &end, math::vec3 &hit, const std::vector<math::vec3> &vertices, const std::vector<uint32_t> &triangles);

private:
    std::string m_physics_file_path;
    std::string m_temp_folder_path;
    std::vector<uint32_t> m_triangles0;
    std::vector<uint32_t> m_triangles1;
    std::vector<uint32_t> m_triangles2;
    std::vector<uint32_t> m_triangles3;
    std::vector<uint32_t> m_triangles4;
    std::vector<math::vec3> m_vertices0;
    std::vector<math::vec3> m_vertices1;
    std::vector<math::vec3> m_vertices2;
    std::vector<math::vec3> m_vertices3;
    std::vector<math::vec3> m_vertices4;
};

#endif
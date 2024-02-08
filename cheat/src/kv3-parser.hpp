#ifndef KV3_PARSER_HPP
#define KV3_PARSER_HPP

#include <windef.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <variant>
#include <optional>

#include <util.hpp>

struct value_struct_t;

using object_t = std::map<std::string, value_struct_t>;
using array_t = std::vector<value_struct_t>;
using value_t = std::variant<std::string, object_t, array_t>;

struct value_struct_t
{
    value_t value;
};

class c_kv3_parser
{
public:
    c_kv3_parser() = default;
    ~c_kv3_parser() = default;

public:
    void parse(const std::string &content);
    std::string get_value(const std::string &path) const;
    std::vector<std::string> find_key_paths_with_key_name(const std::string &search_key);

public:
    template <typename Ty>
    std::vector<Ty> bytes_to_vec(const std::string &bytes)
    {
        const auto num_bytes = bytes.size() / 3;
        const auto num_elements = num_bytes / sizeof(Ty);

        std::vector<Ty> vec;
        vec.resize(num_elements + 1);

        const char *p1 = bytes.c_str();
        uint8_t *p2 = reinterpret_cast<uint8_t *>(vec.data());
        while (*p1 != '\0')
        {
            if (*p1 == ' ')
            {
                ++p1;
            }
            else
            {
                *p2++ = get_byte(p1);
                p1 += 2;
            }
        }

        return vec;
    }

private:
    void find_key_paths_with_key_name(const value_t &root, const std::string &search_key, std::vector<std::string> &paths, const std::string &current_path = "") const;
    void skip_comments_and_metadata();
    void skip_whitespace();
    void skip_comments();
    size_t get_key_or_value_end();
    value_struct_t parse_value();
    value_struct_t parse_byte_array();
    value_struct_t parse_object();
    value_struct_t parse_array();
    std::string join(const std::vector<std::string> &vec, const std::string &delim);

private:
    value_t parsed_data;
    std::string content;
    size_t index;
};

#endif

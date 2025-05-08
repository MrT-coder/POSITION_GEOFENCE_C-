#pragma once
#include <vector>
#include <string>

std::vector<uint8_t> encode_message(const std::string& payload);
std::string decode_message(const std::vector<uint8_t>& raw);

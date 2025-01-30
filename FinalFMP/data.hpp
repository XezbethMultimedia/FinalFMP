#pragma once
#include <iostream>
#include <fstream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

namespace core {
	class object {
	public:
		string name = "object";
		int pos_x = 0;
		int pos_y = 0;
		int siz_x = 0;
		int siz_y = 0;
	};

	void to_json(json& j, const object& o) {
		j = json{
			{"name", o.name},
			{"pos_x", o.pos_x},
			{"pos_y", o.pos_y},
			{"siz_x", o.siz_x},
			{"siz_y", o.siz_y}
		};
	}

	void from_json(const json& j, object& o) {
		j.at("name").get_to(o.name);
		j.at("pos_x").get_to(o.pos_x);
		j.at("pos_y").get_to(o.pos_y);
		j.at("siz_x").get_to(o.siz_x);
		j.at("siz_y").get_to(o.siz_y);
	}
}
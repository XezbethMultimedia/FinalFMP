#include <iostream>
#include <fstream>
#include "json.hpp"

namespace core {

	using json = nlohmann::json;

	namespace object {

		class object {
		public:
			std::string name = "object";
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

	namespace engine {

		class engine {
		private:
			object::object* pObject = NULL;
			int size = 0;
		public:
			void lcObject() {
				size = 0;

				std::ifstream file("cObject.json");
				json jObject = json::parse(file);

				for (json::iterator i = jObject.begin(); i != jObject.end(); i++) {
					size++;
				}

				pObject = new object::object[size];
				size = 0;

				for (json::iterator i = jObject.begin(); i != jObject.end(); i++) {
					*(pObject + size) = i.value().template get<object::object>();
					std::cout << i.key() << " loaded: " << i.value() << "\n";
					size += 1;
				}
			}

			void clear() {
				delete[] pObject;
				std::cout << "Cleard up!\n";
			}
		};
	}
}

int main() {
	core::engine::engine engine;
	engine.lcObject();
	engine.clear();
	return 0;
}
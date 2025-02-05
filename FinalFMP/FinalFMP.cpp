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

	namespace entity {

		class entity : public object::object {
		public:
			int hp = 0;
			int xp = 0;
			int lv = 0;

			int atk = 0;
			int def = 0;
			int dmg = 0;

			int xp2lvl = 150;

			bool alive = true;

			void death() {
				if (hp == 0) {
					alive = false;
				}
			}
			void lvlup() {
				if (xp == xp2lvl) {
					lv += 1;
				}
			}
		};

		void to_json(json& j, const entity& e) {
			j = json{
				{"name", e.name},
				{"pos_x", e.pos_x},
				{"pos_y", e.pos_y},
				{"siz_x", e.siz_x},
				{"siz_y", e.siz_y},
				{"hp", e.hp},
				{"xp", e.xp},
				{"lv", e.lv},
				{"atk", e.atk},
				{"def", e.def},
				{"dmg", e.dmg},
			};
		}

		void from_json(const json& j, entity& e) {
			j.at("name").get_to(e.name);
			j.at("pos_x").get_to(e.pos_x);
			j.at("pos_y").get_to(e.pos_y);
			j.at("siz_x").get_to(e.siz_x);
			j.at("siz_y").get_to(e.siz_y);

			j.at("hp").get_to(e.hp);
			j.at("xp").get_to(e.xp);
			j.at("lv").get_to(e.lv);

			j.at("atk").get_to(e.atk);
			j.at("def").get_to(e.def);
			j.at("dmg").get_to(e.dmg);
		}
	}

	namespace item {

		class item : public object::object {
		public:
			std::string stat;
			int value = 0;
			int range = 0;
		};

		void to_json(json& j, const item& i) {
			j = json{
				{"name", i.name},
				{"pos_x", i.pos_x},
				{"pos_y", i.pos_y},
				{"siz_x", i.siz_x},
				{"siz_y", i.siz_y},
				{"stat", i.stat},
				{"value", i.value},
				{"range", i.range}
			};
		}

		void from_json(const json& j, item& i) {
			j.at("name").get_to(i.name);
			j.at("pos_x").get_to(i.pos_x);
			j.at("pos_y").get_to(i.pos_y);
			j.at("siz_x").get_to(i.siz_x);
			j.at("siz_y").get_to(i.siz_y);
			j.at("stat").get_to(i.stat);
			j.at("value").get_to(i.value);
			j.at("range").get_to(i.range);
		}
	}

	namespace engine {

			object::object* pObject = NULL;
			entity::entity* pEntity = NULL;
			item::item* pItem = NULL;

			std::string sTitle = R"(
 _____                                                                                      _____ 
( ___ )                                                                                    ( ___ )
 |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   | 
 |   |  ______   __       ______   __    __   ______   __   __   ______  ______   __        |   | 
 |   | /\  ___\ /\ \     /\  ___\ /\ "-./  \ /\  ___\ /\ "-.\ \ /\__  _\/\  __ \ /\ \       |   | 
 |   | \ \  __\ \ \ \____\ \  __\ \ \ \-./\ \\ \  __\ \ \ \-.  \\/_/\ \/\ \  __ \\ \ \____  |   | 
 |   |  \ \_____\\ \_____\\ \_____\\ \_\ \ \_\\ \_____\\ \_\\"\_\  \ \_\ \ \_\ \_\\ \_____\ |   | 
 |   |   \/_____/ \/_____/ \/_____/ \/_/  \/_/ \/_____/ \/_/ \/_/   \/_/  \/_/\/_/ \/_____/ |   | 
 |   |                             ______   ______  ______                                  |   | 
 |   |                            /\  == \ /\  == \/\  ___\                                 |   | 
 |   |                            \ \  __< \ \  _-/\ \ \__ \                                |   | 
 |   |                             \ \_\ \_\\ \_\   \ \_____\                               |   | 
 |   |                              \/_/ /_/ \/_/    \/_____/                               |   | 
 |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___| 
(_____)                                                                                    (_____)
)";

			int size = 0;

			void title() {
				std::cout << sTitle << "\n";
			}

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
					size ++;
				}
			}

			void lcEntity() {
				size = 0;

				std::ifstream file("cEntity.json");
				json jEntity = json::parse(file);

				for (json::iterator i = jEntity.begin(); i != jEntity.end(); i++) {
					size++;
				}

				pEntity = new entity::entity[size];
				size = 0;

				for (json::iterator i = jEntity.begin(); i != jEntity.end(); i++) {
					*(pEntity + size) = i.value().template get<entity::entity>();
					std::cout << i.key() << " loaded: " << i.value() << "\n";
					size++;
				}
			}

			void lcItem() {
				size = 0;

				std::ifstream file("cItem.json");
				json jItem = json::parse(file);

				for (json::iterator i = jItem.begin(); i != jItem.end(); i++) {
					size++;
				}

				pItem = new item::item[size];
				size = 0;

				for (json::iterator i = jItem.begin(); i != jItem.end(); i++) {
					*(pItem + size) = i.value().template get<item::item>();
					std::cout << i.key() << " loaded: " << i.value() << "\n";
					size++;
				}
			}

			static int* findPointer(entity::entity& entity, std::string name) {
				if (name == "hp") {
					return &entity.hp;
				}
				else if (name == "xp") {
					return &entity.xp;
				}
				else if (name == "lv") {
					return &entity.lv;
				}
				else if (name == "atk") {
					return &entity.atk;
				}
				else if (name == "def") {
					return &entity.def;
				}
				else if (name == "dmg") {
					return &entity.dmg;
				}
				else {
					std::cout << "That stat does not exist!\n";
					return NULL;
				}
			}

			void showStats(entity::entity entity) {
				std::cout << "Name: " << entity.name << "\n"
					<< "Hp: " << entity.hp << "\n"
					<< "Xp: " << entity.xp << "\n"
					<< "Lv: " << entity.lv << "\n"
					<< "Atk: " << entity.atk << "\n"
					<< "def: " << entity.def << "\n"
					<< "dmg: " << entity.dmg << "\n";
			}

			void useItem(item::item item, entity::entity& entity) {
				int* pointer = findPointer(entity, item.stat);
				*pointer += item.value;

				std::cout << entity.name << " used: " << item.name << "\n";

				showStats(entity);
			}

			void stopItem(item::item item, entity::entity& entity) {
				int* pointer = findPointer(entity, item.stat);
				*pointer -= item.value;

				std::cout << entity.name << " put away: " << item.name << "\n";

				showStats(entity);
			}

			void clear() {
				delete[] pObject;
				delete[] pEntity;
				delete[] pItem;
				std::cout << "Cleared up!\n";
			}
	}
}

int main() {
	using namespace core::engine;

	lcEntity();
	lcItem();

	title();

	useItem(pItem[3], pEntity[1]);
	stopItem(pItem[3], pEntity[1]);
	clear();
	return 0;
}
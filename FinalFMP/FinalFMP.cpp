#include <fstream>
#include "json.hpp"
#include "data.hpp"
using json = nlohmann::json;

int main() {
	int num = 0;

	std::ifstream f("objects.json");
	json objects_json = json::parse(f);

	for (json::iterator it = objects_json.begin(); it != objects_json.end(); it++) {
		num += 1;
	}

	core::object* objects = new core::object[num];
	num = 0;

	for (json::iterator it = objects_json.begin(); it != objects_json.end(); it++) {
		objects[num] = it.value().template get<core::object>();
		std::cout << it.key() << " loaded: " << it.value() << "\n";
		num += 1;
	}

	delete[] objects;
	std::cout << "Deleted Objects!\n";
	return 0;
}
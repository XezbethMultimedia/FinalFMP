#include <fstream>
#include "json.hpp"
#include "data.hpp"
using json = nlohmann::json;

int main() {
	int num = 0;

	std::ifstream f("objects.json");
	json objects_json = json::parse(f);

	std::cout << objects_json.dump(4) << "\n";

	for (json::iterator it = objects_json.begin(); it != objects_json.end(); it++) {
		std::cout << num << " : " << it.key() << " : " << it.value() << "\n";
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
	return 0;
}
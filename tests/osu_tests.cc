#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#define private public

#include "visualizer/game.h"

using namespace final_project;

TEST_CASE("Circles") {
    Circle c(glm::vec2(100, 100), 200, 20, 100, 3, ci::Color(0, 0, 0));
    SECTION("inRange") {
        REQUIRE(c.inRange(100)); // before
        REQUIRE(c.inRange(370)); // after
        REQUIRE(!c.inRange(99)); // before
        REQUIRE(!c.inRange(371)); // after
    }

    SECTION("early hit") {
        c.hit(105);
        REQUIRE(c.isHit(110));
    }

    SECTION("hit in range") {
        c.hit(200);
        REQUIRE(c.isHit(200));
    }

    SECTION("late hit") {
        c.hit(400);
        REQUIRE(!c.isHit(450));
        REQUIRE(c.isMiss());
    }

    SECTION("miss") {
        REQUIRE(c.isMiss());
    }
}

TEST_CASE("Spinner") {
    Spinner spinner(100, 400, 600);
    SECTION("Not Spun") {
        REQUIRE(spinner.isMiss());
    }

    SECTION("Spin") {
        spinner.spin(20);
        REQUIRE(spinner.spins_ == 20);
        REQUIRE(spinner.rotation_ == 20);
    }

    SECTION("Counter spin") {
        spinner.spin(-10);
        REQUIRE(spinner.spins_ == 10);
        REQUIRE(spinner.rotation_ == -10);
    }

    SECTION("Multiple Spins") {
        spinner.spin(-5);
        spinner.spin(10);
        spinner.spin(-2);
        spinner.spin(-1.5);
        spinner.spin(1.5);
        REQUIRE(spinner.spins_ == 20);
        REQUIRE(spinner.rotation_ == 3);
    }

    SECTION("Clear spinner") {
        spinner.spin(2000);
        REQUIRE(!spinner.isMiss());
    }

    SECTION("inRange") {
        REQUIRE(spinner.inRange(500));
        REQUIRE(!spinner.inRange(100));
        REQUIRE(!spinner.inRange(900));
    }

    SECTION("isAfter") {
        REQUIRE(!spinner.isAfter(40));
        REQUIRE(spinner.isAfter(700));
    }
}

TEST_CASE("Asset Loader") {
    /*
     * Not testing:
     * getAssetsPath
     * getSongsPath
     * getSkinsPath
     * ------------- simply returns a concatenated string
     * requestImage(song index)
     * getSongList
     * ------------- Asset folder changes regularly and tests will not be able to stay up to date
     */

    SECTION("getMapList") {
        std::vector<std::string> list = asset_loader.getMapList("320118 Reol - No title");
        REQUIRE(list.size() == 15);
    }

    SECTION("Broken request") {
        REQUIRE_THROWS_AS(asset_loader.requestImage("unknown", "not a file"), std::exception);
        REQUIRE_THROWS_AS(asset_loader.requestImage("unknown"), std::exception);
        REQUIRE_THROWS_AS(asset_loader.requestAudio("unknown song", "not an mp3"), std::exception);
    }
}

TEST_CASE("Map Loader") {
    /*
     * Not testing:
     * getAssetsPath
     * getSongsPath
     * getSkinsPath
     * ------------- simply returns a concatenated string
     * getMapList
     * ------------- Same as AssetLoader
     * requestMap (map index)
     * getSongList
     * ------------- Asset folder changes regularly and tests will not be able to stay up to date
     */

    MapLoader map_loader;
    SECTION("Load Map") {
        Map map = map_loader.requestMap("320118 Reol - No title", "Reol - No title (VINXIS) [byfaR's Hard].osu");
        REQUIRE(map.getTitle() == "No title"); // yup, the song is called No title :)
        REQUIRE(map.getVersion() == "byfaR's Hard");
    }
}

// Nothing in Cursor to test (simply just draws)

// Nothing in Hud to test (simply just draws)

// Nothing in EndScreen to test (simply just draws)

TEST_CASE("InputPoint") {
    InputPoint ip(150, glm::vec2(10, 20), true, false, true, false);
    SECTION("Operator <<") {
        std::stringstream s;
        s << ip;
        REQUIRE(s.str() == "150,10,20,5");
    }
    SECTION("Operator >>") {
        std::ifstream file;
        file.open("tests\\data\\input_point");

        REQUIRE(file.is_open());
        InputPoint ip;
        file >> ip;
        REQUIRE(ip.key_one_pressed_);
        REQUIRE(ip.r_mouse_pressed_);
        REQUIRE(ip.time_ == 150);
        REQUIRE(ip.position_.x == 10);
        REQUIRE(ip.position_.y == 20);
    }
}

TEST_CASE("Input") {
    Input input;
    input.update(50, glm::vec2(10, 20), std::set<int>{ci::app::KeyEvent::KEY_z}, false, true);
    input.update(80, glm::vec2(30, 20), std::set<int>{ci::app::KeyEvent::KEY_x}, true, true);
    input.update(93, glm::vec2(50, 234), std::set<int>{}, false, false);

    SECTION("Get Input") {
        InputPoint ip = *input.getInput(52);
        REQUIRE(ip.time_ == 50);
    }

    SECTION("Get inputs num") {
        std::vector<InputPoint*> ips = input.getInputs(2);
        REQUIRE(ips[0]->time_ == 80);
        REQUIRE(ips[1]->time_ == 93);
    }

    SECTION("Get inputs time, num") {
        std::vector<InputPoint*> ips = input.getInputs(82, 2);
        REQUIRE(ips[0]->time_ == 50);
        REQUIRE(ips[1]->time_ == 80);
    }

    SECTION("Operator <<") {
        std::stringstream s;
        s << input;
        REQUIRE(s.str().substr(0, 10) == "50,10,20,9");
        REQUIRE(s.str().substr(10, 11) == "80,30,20,14");
    }

    SECTION("Operator >>") {
        std::ifstream file;
        file.open("tests\\data\\input");

        REQUIRE(file.is_open());
        Input input_;
        file >> input_;
        REQUIRE(input_.getInputs().size() == 3);
        InputPoint ip = *input_.getInputs().at(0);
        REQUIRE(ip.key_one_pressed_);
        REQUIRE(ip.l_mouse_pressed_);
        REQUIRE(ip.time_ == 50);
        REQUIRE(ip.position_.x == 10);
        REQUIRE(ip.position_.y == 20);
    }
}

TEST_CASE("Map") {
    Map map;
    SECTION("overloading") {
        std::ifstream file("..\\..\\assets\\dlzosu!\\Songs\\320118 Reol - No title\\Reol - No title (VINXIS) [spin].osu");
        file >> map;

        REQUIRE(map.audio_filename_ == "No title.mp3");
        REQUIRE(map.background_filename_ == "Irre.jpg");
    }

    SECTION("File format") {
        std::ifstream file("..\\..\\assets\\dlzosu!\\Songs\\320118 Reol - No title\\Lemur.jpg");
        REQUIRE_THROWS_AS(file >> map, std::exception);
    }
}
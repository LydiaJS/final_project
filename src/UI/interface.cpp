#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp> //idfk might not need this 
#include "ftxui/component/component.hpp"  //for a lot of dif shit
#include "ftxui/component/component_options.hpp"  //menu_entry
#include "ftxui/component/screen_interactive.hpp" //screen interactive
#include <iostream>
 
int main(void) {
  using namespace ftxui;

  auto screen = ScreenInteractive::TerminalOutput();

  int selected = 0; //selected element number
  int level = 0; //top level vs thread level
  std::vector<std::string> menu_entries = {
      "Tech test", "Politics", "Climate", "Other"
  };

  auto menu_option = MenuOption(); //Options obj

  auto menu = Menu(&menu_entries, &selected, &menu_option);

  //exicutes on enter
  menu_option.on_enter = [&selected, &level, &menu_entries] {
    switch(level){
      case 0:
        //Board List
        menu_entries.clear();
        menu_entries = {"Tech", "Politics", "Climate", "Other"};
        break;
      case 1:
        menu_entries.clear();
        menu_entries = {"back hello", "Two2", "Three3", "Four4"};
        break;
      case 2:
      //POST SELECT
        menu_entries.clear();
        menu_entries = {"One", "Two", "Three", "Four"};
        break;
    }

    switch(selected){
      case 0:
        if(level != 0){
          level -= 1;
        }
      default:
        if(level < 2){
          level += 1;
        }
    }
  };

auto buttons = Container::Vertical({
    Button("Catologue", [&] { /* on click*/}),
    Button("Thread List", [&] {}),
});

auto renderer = Renderer(menu, [&] {

  return vbox({
    hbox(text("selected = "), text(std::to_string(selected))) | border,
    hbox(
      vbox({
        hbox({
          menu->Render(),
        }),
      }),
      buttons -> Render()
    )
  });
});
  
  screen.Loop(renderer);

  return EXIT_SUCCESS;
}
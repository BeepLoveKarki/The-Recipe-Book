#include "stdafx.h"
#include "intro.h"
#include "recipeday.h"
#include "recipelist.h"
#include "addrecipe.h"
#include "about.h"
#include "editrecipe.h"
#include <iostream>
#include <string>
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/WWidget.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WAnimation.h>
#include <Wt/WMenu.h>
using namespace std;

class HelloApplication : public Wt::WApplication
{
public:
	HelloApplication(const Wt::WEnvironment& env); //Constructor for application environment
private:
	string abimg = "img/main.jpg",fimg = "img/foot.jpg"; //image path declaration
	intro i{abimg}; //Instance of intro class
	recipelist rb; //Instance of recipelist class
	addrecipe ar; //Instance of addrecipe class
	recipeday rd; //Instance of video class
	about au{fimg}; //Instance of about us class
	editrecipe er; //Instance of editrecipe class
	Wt::WBootstrapTheme *theme;  //Bootstrap theme declaration
	Wt::WNavigationBar *navigation; //Navigation bar
	Wt::WStackedWidget *contents; //Widgest stack for the sections of page
	Wt::WMenu *menu; //Menu items
    void setNavigationBar(); //Function to add navigation bar
};

HelloApplication::HelloApplication(const Wt::WEnvironment& env) : WApplication(env) //initalizating bootstrap constructor
{
    useStyleSheet("/style/style.css"); //Load custom css file
	root()->setStyleClass("home"); //Add css class to root
	theme = new Wt::WBootstrapTheme();  //Theme initialization
	theme->setResponsive(true);  //Make theme responsive
	theme->setVersion(Wt::BootstrapVersion::v3);  //Set bootstrap version
	setTheme(shared_ptr<Wt::WTheme>(theme)); //Apply theme to the environment
	setTitle("The Recipe Book"); //Setpage title
	root()->setPositionScheme(Wt::PositionScheme::Relative);  //make page position relative
	setNavigationBar(); //call function to make navigation bar
}

void HelloApplication::setNavigationBar()  //Add navigation bar function
{
	navigation = root()->addWidget(Wt::cpp14::make_unique<Wt::WNavigationBar>()); //Navigation bar initialization
	navigation->setResponsive(true);  //make navigation bar responsive
	navigation->addStyleClass("navbar-fixed-top");//add style class to the navigation bar
	navigation->decorationStyle().setBackgroundColor(Wt::WColor("#0000FF")); //setbackground color
	navigation->setWidth("100%"); //set width 100%
	navigation->setAttributeValue("style", "border-bottom:none"); //add style attribute
	navigation->setTitle("The Recipe Book","/");
	contents = root()->addWidget(Wt::cpp14::make_unique<Wt::WStackedWidget>()); //Widget to hold other child widgets
	auto menu = Wt::cpp14::make_unique<Wt::WMenu>(contents); //Initialize menu widget
	auto menu_ = navigation->addMenu(std::move(menu),Wt::AlignmentFlag::Right); //add menu to navigation
	menu_->setId("lists");  //setId of menu
	menu_->setMargin("10px", Wt::Side::Right);
	menu_->addItem("Introduction")->setLink(Wt::WLink("#i"));//add menu item with link
	menu_->addItem("Add Recipe")->setLink(Wt::WLink("#ar")); //add menu item with link
	menu_->addItem("Update Recipe")->setLink(Wt::WLink("#ur")); //add menu item with link
	menu_->addItem("Recipe List")->setLink(Wt::WLink("#rb")); //add menu item with link
	menu_->addItem("Recipe Of The Day")->setLink(Wt::WLink("#rd"));//add menu item with link
	menu_->addItem("About Us")->setLink(Wt::WLink("#au")); //add menu item with link
	root()->addWidget(i.makeintro())->setAttributeValue("style","max-width:1200px; margin:auto;"); //add text and image in Introduction part
	root()->addWidget(ar.makeaddrecipe())->setAttributeValue("style", "max-width:1200px; margin:auto;"); //add add recipe option in Add Recipe part
	root()->addWidget(er.makeeditrecipe())->setAttributeValue("style", "max-width:1200px; margin:auto;"); //add add recipe option in Add Recipe part
	root()->addWidget(rb.makerecipelist())->setAttributeValue("style", "max-width:1200px; margin:auto;"); //add recipe lists in Recipe List part
	root()->addWidget(rd.showrday())->setAttributeValue("style", "max-width:1200px; margin:auto;"); //add to recipe for the day
	root()->addWidget(au.makeabout()); //add about us data in About us part
}

int main(int argc, char **argv)
{
	return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) { //return running environment
		return Wt::cpp14::make_unique<HelloApplication>(env); //return GUI of the running environment
	});
}


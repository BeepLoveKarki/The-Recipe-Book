#pragma once 
#include <iostream>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WWidget.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WImage.h>
#include <string>
#include <ctime>
#include <chrono>
#include <sstream>
#include <Wt/WAnimation.h>

using namespace std;
class about {
public:
	about(string); //constructor initialization
	~about() {}; //destructor initialization
	auto makeabout(); //function declaration to return container
private:
	Wt::WImage *image; //image widget declaration
	Wt::WText* txt; //text widget declaration
	Wt::WText *copy;//copyright widget declaration
	Wt::WText *email;//email widget declaration
	Wt::WText *em; //emal text declaration
	string img; //img path declaration
	template<typename T> void addtext(T& container); //function declaration to add text
	template<typename T> void addcopy(T& container); //function declaration to add copyright
	template<typename T> void addemail(T& container); //function declaration to add contact email
};

about::about(string img) { //constructor definition
	this->img=img; //parameterized constructor
}

auto about::makeabout() { //function definition to return container
	auto container = Wt::cpp14::make_unique<Wt::WContainerWidget>(); //add container widget
	container->setMargin("30px", Wt::Side::Top); //add margin to top of container
	container->setId("au"); //set id to class
	//container->setMargin("10px", Wt::Side::Bottom); //add margin to bottom of container
    image = container->addWidget(Wt::cpp14::make_unique<Wt::WImage>(Wt::WLink(img)));//add image widget
	image->setAlternateText("Happy Cooking"); //add alternate class to image
	image->setStyleClass("img-responsive center-block"); //add style class to image
	image->decorationStyle().setCursor(Wt::Cursor::PointingHand); //add cursor design to image
	addtext(container); //call function to add text
	container->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000)); //add animation on load
	return container; //return container to main file
}

template<typename T> 
void about::addtext(T& container) {
	string text ="<h3>Developed by Biplab Karki and Jay Kishan Panjiyar</h3>"; //string for text
	txt = container->addWidget(Wt::cpp14::make_unique<Wt::WText>(text)); //add text widget to container
	txt->setStyleClass("reactive text-center"); //add style classes to text
	txt->setMargin("5px", Wt::Side::Top); //add margin to top
	addemail(container); //call function to add email
}

template<typename T>
void about::addemail(T& container) {
	em = container->addWidget(Wt::cpp14::make_unique<Wt::WText>("<h4>Have some words to say??</h4>")); //text to email
	email =container->addWidget(Wt::cpp14::make_unique<Wt::WText>("<h4>Email Us</h4>")); //email widget text
	em->setStyleClass("reactive text-center"); //set style class to text for email
	email->setStyleClass("reactive text-center"); //set style class to email widget
	email->decorationStyle().setCursor(Wt::Cursor::PointingHand); //set cursorstyle for email widget
	email->decorationStyle().setForegroundColor(Wt::WColor("#0000EE")); //set foreground color for email widget
	email->clicked().connect([=]{ //bind click event to email link widget
		HelloApplication::instance()->redirect("mailto:booktherecipe@gmail.com"); //open email on click
	});
	addcopy(container); //add copyright
}

template<typename T>
void about::addcopy(T& container) {
	struct tm ltm; //structure to hold time
	time_t now = time(0); //get present time
	localtime_s(&ltm,&now); //store time parameters to the structure
	string s1 = "<h5>Copyright &copy; ", s2 = " The Recipe Book</h5>"; //some text
	string s3=to_string(1900 + ltm.tm_year); //year value
	string copyright = s1+s3+s2; //add strings
	copy = container->addWidget(Wt::cpp14::make_unique<Wt::WText>(copyright)); //add copyright text widget
	copy->setStyleClass("reactive text-center"); //add style class to copyright text widget
	copy->setMargin("5px", Wt::Side::Top);
}


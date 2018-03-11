#pragma once
#include "form.h"
#include "emailmodal.h"
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WWidget.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WImage.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WRegExpValidator.h>
#include <Wt/WAnimation.h>

using namespace std;

class addrecipe {
public:
	addrecipe() {}; //constructor declaration
	~addrecipe() {}; //desctrunctor declaration
	auto makeaddrecipe(); //function declaration to return container
private:
	emailmodal em;
	form f; //instance of dialog class
	Wt::WText *head; //text declaration for heading
	Wt::WText *info; //text declaration for info
	Wt::WPushButton *button; //button declaration for adding recipe items
	Wt::WLineEdit* email;//text area for email
	Wt::WText* err; //error text widget
	template<typename T> void addhead(T& container); //function declaration to add heading and text
	template<typename T> void addbutton(T& container); //function declaration to add heading and text
	template<typename T> void m(T& container); //function to validate and work as per
	bool checkmail(string); //function to check if user pre-exists
	template<typename T> void goodone(T&);
};

auto addrecipe::makeaddrecipe() { //function declaration to return the container
	auto container = Wt::cpp14::make_unique<Wt::WContainerWidget>(); //add container widget
	container->setId("ar"); //provide id to the container
	container->setHeight("215px");//set height of container
	container->setStyleClass("text-center"); //set style class to container
	container->decorationStyle().setBackgroundColor(Wt::WColor("#6495ED")); //add background color to the container widget
	container->decorationStyle().setForegroundColor(Wt::WColor("#FFFFFF"));//add foreground color to the container widget
	addhead(container); //function to add heading
	container->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000)); //add animation on load
	return container; //return container to main file
}

template<typename T>
void addrecipe::addhead(T& container) { //function definition to add heading and text
	head = container->addWidget(Wt::cpp14::make_unique<Wt::WText>("<h1 style='margin-top:30px;'>Add Your Recipe</h1>")); //Add heading to the container
	info = container->addWidget(Wt::cpp14::make_unique<Wt::WText>("<h3> Help recipe seekers throughout the world!!! Contribute by sharing your recipe items!!!</h3>")); //add info text to the container
	head->addStyleClass("reactive text-center"); //add style class to the heading
	head->setMargin("50px", Wt::Side::Top); //add margin to top
	head->setHeight("40px"); //setheight of head
	info->addStyleClass("reactive text-center"); //add style class to the info
	head->decorationStyle().setBackgroundColor(Wt::WColor("#EE3B3B")); //add background color to head
	head->decorationStyle().setCursor(Wt::Cursor::PointingHand); //add cursor design to head
	email = container->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>()); //add email field
	email->setValidator(Wt::cpp14::make_unique<Wt::WRegExpValidator>("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,4}")); //add email validation
	email->setStyleClass("input-lg text-center"); //add style classes to field
	email->setPlaceholderText("Enter your email address");
	email->setWidth("30%"); //set width to field
	email->setMargin("5px", Wt::Side::Bottom); //add margin to top
	email->setMargin("15px", Wt::Side::Bottom); //add margin to bottom
	email->setMargin("auto", Wt::Side::Left); //add margin to left
	email->setMargin("auto", Wt::Side::Right); //ad margin to right
	addbutton(container); //call function to add button
}

template<typename T>
void addrecipe::addbutton(T& container) {//function definition to add button to add recipe
	button = container->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Add your recipe"));//add button to add recipe
	button->addStyleClass("btn btn-warning btn-lg center-block"); //add style classes to the button
	button->setDisabled(true); //set disable button at beginning
	button->setId("fg"); //set id to button
	err = container->addWidget(Wt::cpp14::make_unique<Wt::WText>()); //add empty text widget
	err->setInline(false); //set inline property to false
	err->hide(); //hide the text widget
	auto c = container.get(); //get container instance
	email->keyWentDown().connect([=]{
		button->enable(); //enable button
    });
	email->enterPressed().connect([=] {
		m(c); //call validation function
	});
	button->clicked().connect([=] {
		m(c); //call validation function
	});
}

template<typename T>
void addrecipe::m(T& c) {
	string e = f.give(email->text());
	if (e.length()!=0 && email->validate() == Wt::ValidationState::Valid) {
			if (checkmail(e)) {
				goodone(c);
			}
			else {
				try { //exception for no email found
					vector<int> v(5);
					cout << v.at(10) << endl;
				}
				catch (exception ex) {
					em.dostuffs(c, e);
				}
			}
	}
	else {
		err->show(); //show text alert
		err->setText("Please enter a valid email"); //add alert text
		err->setStyleClass("alert alert-danger"); //add class to alert text
		err->setMargin("20px", Wt::Side::Top); //add margin to top
		err->setMargin("auto", Wt::Side::Left | Wt::Side::Right); //add margin to left and right as auto
		err->setWidth("30%"); //add widh to text
		c->setHeight("315px"); //increase height of container
	}
}

bool addrecipe::checkmail(string d) {
	string a;
	ifstream fs; 
	fs.open("files/user_recipe_num.txt"); //open file for reading
	fs >> a;
	if (a.find(d) == string::npos) { //check if email pre exists
		return false;
	}
	else {
		return true;
	}	
}

template<typename T>
void addrecipe::goodone(T& c) {
	err->hide();
	email->setHidden(true); //hide email field
	info->setHidden(true); //hide the info text
	button->setHidden(true); //hide the button
	c->setHeight("1065px");//set height of container
	head->setMargin("50px", Wt::Side::Bottom); //add margin to bottom
	f.decide = 0;
	Wt::WPushButton* can = f.showform(c, f.give(email->text())); //call showform method of form class
	head->setMargin(to_string(30 - 20 * f.find) + "px", Wt::Side::Bottom);
	can->clicked().connect([=] {
		head->setMargin("30px", Wt::Side::Bottom);
		f.button->setHidden(true); //hide buttons on click
		can->setHidden(true);
		f.done->setHidden(true);
		for (auto& l : f.labels) { //hide all form elements
			l->setHidden(true);
		}
		for (auto& b : f.boxes) {
			b->setHidden(true);
		}
		for (auto& t : f.texts) {
			t->setHidden(true);
		}
		for (auto& br : f.b) {
			br->setHidden(true);
		}
		f.labels.clear(); //clear the vectors
		f.boxes.clear();
		f.texts.clear();
		f.b.clear();
		email->setHidden(false); //show email field
		info->setHidden(false); //show the info text
		button->setHidden(false); //show the button
		email->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000)); //show animation
		info->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000)); //show animation
		button->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000)); //show animation
		c->setHeight("255px"); //set height of container
		Wt::WApplication::instance()->redirect("#ar"); //redirect to top
	});
}





#pragma once
#include "form.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WWidget.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WImage.h>
#include <Wt/WAnchor.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WAnimation.h>
#include <Wt/WRegExpValidator.h>

using namespace std;

class editrecipe {
public:
	editrecipe() {}; //constructor
	~editrecipe() {}; //destructor
	auto makeeditrecipe(); //auto function declaration to return container
private:
	vector<Wt::WImage*>img; //widget to hold image 
	vector<Wt::WText*> label; // text widget to hold datas
	vector<Wt::WBreak*> brk; //vector of line breaks
	vector<string> data,mu; //vector string of data
	string all; //string to hold email and contents
	form f; //instance of form class
	Wt::WText *head,*head1,*err; //heading text widget declaration
	Wt::WLineEdit *email; //email field declaration
	Wt::WPushButton *button,*btn; //button declaration
	template<typename T> void addheading(T& container); //class to add heading
	template<typename T> void addbutton(T& container); //class to add button
	template<typename T> void m(T& container); //function to call data
	template<typename T> void editrecipe::replace(T&, string); //add new data
	bool checkif(string); //function to check if exists
	void error();//error function
	void separate(); //separate by !
	template<typename T>void showf(T&,int); //edit form
	string a[6]; //data
	int gi,hi,ii,u;
};

auto editrecipe::makeeditrecipe() {  //function definition to return container
	gi = 0;
	hi = 0;
	ii = 0;
	u = 0;
	auto container = Wt::cpp14::make_unique<Wt::WContainerWidget>(); //add container widget
	container->setId("ur");//declare id to the container
	container->setHeight("195px");//set height of container
	container->decorationStyle().setBackgroundColor(Wt::WColor("#DC143C")); //add background color
	container->decorationStyle().setForegroundColor(Wt::WColor("#FFFFFF")); //add foreground(text) color
	addheading(container); //add heading
	container->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000)); //add animation on load
	return container; //return container to main file
}

template<typename T>
void editrecipe::addheading(T & container)
{
	head = container->addWidget(Wt::cpp14::make_unique<Wt::WText>("<h1 style='margin-top:30px;'>Update Your Recipe</h1>")); //Add heading to the container
	head->addStyleClass("reactive text-center"); //add style class to the heading
	head->setMargin("50px", Wt::Side::Top); //add margin to top
	head->setMargin("30px", Wt::Side::Bottom); //add margin to bottom
	head->setHeight("40px"); //setheight of head
	head->decorationStyle().setBackgroundColor(Wt::WColor("#8A2BE2")); //add background color to head
	head->decorationStyle().setCursor(Wt::Cursor::PointingHand); //add cursor design to head
	email = container->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>()); //add email field
	email->setStyleClass("input-lg text-center"); //add style classes to field
	email->setPlaceholderText("Enter your email address");
	email->setValidator(Wt::cpp14::make_unique<Wt::WRegExpValidator>("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,4}")); //add email validation
	email->setWidth("30%"); //set width to field
	email->setMargin("20px", Wt::Side::Bottom); //add margin to top
	email->setMargin("auto", Wt::Side::Left); //add margin to left
	email->setMargin("auto", Wt::Side::Right); //ad margin to right
	addbutton(container); //call function to add button
}

template<typename T>
void editrecipe::addbutton(T& container) {//function definition to add button to add recipe
	button = container->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Start Updating"));//add button to add recipe
	button->addStyleClass("btn btn-info btn-lg center-block"); //add style classes to the button
	button->setDisabled(true); //set disable button at beginning
	button->setId("baby");
	err = container->addWidget(Wt::cpp14::make_unique<Wt::WText>()); //add empty text widget
	err->setInline(false); //set inline property to false
	err->hide(); //hide the text widget
	auto c = container.get(); //get container instance
	email->keyWentDown().connect([=]{
		button->enable(); //enable button
	});
	email->enterPressed().connect([=] {
		m(c);//call function
	});
	button->clicked().connect([=] {
		m(c); //call function
	});
}

template<typename T>
void editrecipe::m(T& c) {
	if (f.give(email->text()).length() != 0 && email->validate() == Wt::ValidationState::Valid) {
		if (checkif(f.give(email->text()))) {
			img.clear();
			label.clear();
			brk.clear();
			err->setHidden(true);
			email->setHidden(true); //hide email widget
			button->setHidden(true); //hide the button
			head->setText("<h1 style='margin-top:30px;'>Choose Among Your Saved Recipes!!!</h1>");
			if (gi == 0) {
				head->setMargin(to_string(30) + "px", Wt::Side::Bottom);
			}
			else {
				string a = to_string(-5 * gi*gi - 5 * gi - 40);
				head->setMargin(a + "px", Wt::Side::Bottom); //set dynamic height
			}
			c->setHeight(to_string(size(data) * 550 + 100) + "px"); //resize container's height
			mu = data;
			if (mu.size() == 0) {
				head->setText("<h1 style='margin-top:30px;'>Sorry No Entered Recipes Found!!!</h1>");
				c->setHeight("150 px"); //resize container's height
			}
				for (auto& a : data) {
					replace(c, a);
				}
				if (mu.size() == 0) {
					btn = c->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("OK")); //add cancel button
					btn->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::Fade, Wt::TimingFunction::Linear, 1000));
				}
				else {
					btn = c->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Cancel")); //add cancel button
					btn->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000));
				}
				btn->setMargin("auto", Wt::Side::Left | Wt::Side::Right); //set auto margin vertically
				btn->setStyleClass("center-block btn btn-lg btn-info"); //add style class
				btn->clicked().connect([=] {
					hi = 1;
					head->setText("<h1 style='margin-top:30px;'>Update Your Recipe</h1>");
					btn->setHidden(true);
					for (auto& a : img) { //hide elements
						a->setHidden(true);
					}
					for (auto& b : brk) {
						b->setHidden(true);
					}
					for (auto& cd : label) {
						cd->setHidden(true);
					}
					head->setMargin(to_string(30) + "px", Wt::Side::Bottom);
					c->setHeight("195px"); //resize it
					email->setHidden(false); //show email widget
					button->setHidden(false); //show the button
					email->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000));
					button->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000));
					Wt::WApplication::instance()->redirect("#ur"); //redirect
				});
				err->hide();
				int x = -1;
				for (auto& i : img) {
					x++;
					i->setMargin("auto", Wt::Side::Left | Wt::Side::Right); //set auto margin vertically
					i->setStyleClass("center-block"); //add style class
					i->decorationStyle().setCursor(Wt::Cursor::PointingHand);//set cursor type
					i->setAlternateText("Recipe Image"); //set alternate text
					i->setMargin("50px", Wt::Side::Top); //set top margin
					i->setWidth("550px"); //set image width
					i->setHeight("400px"); //set image height
					i->setAttributeValue("onmouseover", "this.style.width='580px'"); //add effect on click
					i->setAttributeValue("onmouseout", "this.style.width='550px'");
					i->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000));
					i->clicked().connect([=] {
						showf(c, x); //function t show form
					});
				}
				int y = -1;
				for (auto& l : label) {
					y++;
					l->setMargin("auto", Wt::Side::Left | Wt::Side::Right); //set auto margin vertically
					l->setStyleClass("text-center"); //add style class
					l->decorationStyle().setCursor(Wt::Cursor::PointingHand);//set cursor type
					l->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000));
					l->clicked().connect([=] {
						showf(c, y); //function to show form
					});
				}
			}
		else {
			error();
			c->setHeight("315px"); //increase height of container
		}
		}
		else {
			error();
			c->setHeight("315px"); //increase height of container
		}
	
}

template<typename T>
void editrecipe::showf(T& container,int b) {
	ii=1;
    head->setText("<h1 style='margin-top:30px;'>Update Your Recipe</h1>");
	vector<string> lu = mu;
	for (auto& i : img) { //hide elements
		i->setHidden(true);
	}
	for (auto& l : label) {
		l->setHidden(true);
	}
	for (auto& b : brk) {
		b->setHidden(true);
	}
	btn->setHidden(true);
	container->setHeight("1105px");//set height of container
	container->setStyleClass("text-center"); //add text center style class
	f.decide = 1;
	string w[6];
	for (int i = 0; i < 6; i++) {
		w[i]= lu.at(b).substr(0, lu.at(b).find_first_of(","));
		lu.at(b).erase(0,lu.at(b).find_first_of(",")+1);
	}
	for (int i = 0; i<6; i++) {
		while (w[i].find("@") != string::npos) { //check if ',' is found
			w[i].replace(w[i].find("@"), 1, ","); //replace @ with comma again
		}
	}
	for (int i = 0; i<6; i++) {
		f.fr[i] = w[i]; //assign data values to form array
	}
	Wt::WPushButton* can = f.showform(container,f.give(email->text()));//show form
	head->setMargin(to_string(30 - 40 * f.find) + "px", Wt::Side::Bottom);
	Wt::WApplication::instance()->redirect("#ur");//redirect
	can->clicked().connect([=] {
		gi++;
		if (ii == 1 && hi == 1) {
			Wt::WApplication::instance()->refresh();
			Wt::WApplication::instance()->redirect("#ur");//redirect
		}
		else {
			head->setMargin(to_string(30) + "px", Wt::Side::Bottom);
		}
		head->setText("<h1 style='30px'>Choose Among Your Saved Recipes!!!</h1>");
		f.bull->setHidden(true);
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
		f.labels.clear(); 
		f.boxes.clear();
		f.texts.clear();
		f.b.clear();
		for (auto& i : img) { //hide elements
			i->setHidden(false);
			i->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft,Wt::TimingFunction::Linear,1000));
		}
		for (auto& l : label) {
			l->setHidden(false);
			l->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000));
		}
		for (auto& b : brk) {
			b->setHidden(false);
			b->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000));
		}
		btn->setHidden(false);
		btn->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000));
		container->setHeight(to_string(size(mu) *550+100) + "px"); //resize container's height
		Wt::WApplication::instance()->redirect("#ur");//redirect
	});
}

template<typename T>
void editrecipe::replace(T& container,string data) {
	ifstream f; //file stream to read
	for(int i = 0; i<6; i++) {
		a[i] = data.substr(0, data.find_first_of(",")); //separate datas from string
		data.erase(0, data.find_first_of(",") + 1); //erase previous portion of string
	}
	for (int i = 0; i<6; i++) {
		while (a[i].find("@") != string::npos) { //check if ',' is found
			a[i].replace(a[i].find("@"), 1, ","); //replace @ with comma again
		}
	}
	f.open("uploads/" + a[0] + ".jpg"); //open image
	if(f.good()) { //check if image exists
	    img.push_back(container->addWidget(Wt::cpp14::make_unique<Wt::WImage>("uploads/" + a[0] + ".jpg"))); //add image
	}
	else {
		img.push_back(container->addWidget(Wt::cpp14::make_unique<Wt::WImage>("img/logo.jpg"))); //add image
	}
	label.push_back(container->addWidget(Wt::cpp14::make_unique<Wt::WText>("<h3>" + a[1] + "</h3>"))); //add label
    brk.push_back(container->addWidget(Wt::cpp14::make_unique<Wt::WBreak>())); //addline break
}


void editrecipe::error() {
	err->show(); //show text alert
	err->setText("Either the email is invalid or you have added no recipes!!!"); //add alert text
	err->setStyleClass("alert alert-danger text-center"); //add class to alert text
	err->setMargin("20px", Wt::Side::Top); //add margin to top
	err->setMargin("auto", Wt::Side::Left | Wt::Side::Right); //add margin to left and right as auto
	err->setWidth("30%"); //add widh to text
}

bool editrecipe::checkif(string a) {
	stringstream buffer;
	ifstream f("files/recipe/" + a + ".txt"); //open file to read
	if (f.good()) {
		buffer.str(""); //empty the buffer
		buffer << f.rdbuf();//read data to stringstream
		string d(buffer.str()); //add data to buffer
		all = d;
		separate();
		return true;
	}
	else {
		return false;
	}
}

void editrecipe::separate() {
	data.clear();
	stringstream ss(all); //string stream
	string h;
	while (getline(ss, h, '!')) {
		data.push_back(h); //push data to vector string
	}
}



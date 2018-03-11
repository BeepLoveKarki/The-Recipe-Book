#pragma once
#include "recipelist.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WWidget.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WImage.h>
#include <Wt/WAnimation.h>
using namespace std;

class intro //declaration of class
{
public:
	intro(string); //constructor
	~intro(); //destructor
	auto makeintro(); //method declaration with 'auto' return type
private:
	string image,u,v;
	recipelist rl;
	Wt::WImage *img; //image declaration
	Wt::WText  *itext; //text view declaration
	Wt::WText  **ptext; //text view declaration
	void checkfiles(); //check entries
	template<typename a> void addtext(a& container); //template type function delaration to add text
	template<typename a> void addtext1(a& container); //template type function delaration to add additional text
	template<typename a> void addimage(a& container); //template type function delaration to add image
	vector<string>txt, col;
};

template<typename a>  
void intro::addtext(a& container) //template function definition
{
	checkfiles();
	txt.insert(txt.end(),{"<h3>Haslee Free Platform for Kitchen Lovers</h3>","<h3>Marketize your Recipe Items</h3>","<h3>Check out the latest Recipe Items</h3>","<h3>Really useful for Learners</h3>","<h3>Really helpful for Housewives</h3>","<h3>Presently " +u+ " recipe items available</h3>", "<h3>Currently " + v + " members on list</h3>" }); //string array declaration for text
	col.insert(col.end(),{"#00BFFF","#FF1493","#00008B","#8A2BE2","#DC143C","#FF4040" ,"#FF7F00"}); //array of strings for color
	itext=container->addWidget(Wt::cpp14::make_unique<Wt::WText>("<h1>An Open Platform For Kitchen Lovers</h1>")); //add text widget to container (itext)
	itext->setStyleClass("reactive text-center"); //add classes to itext
	itext->decorationStyle().setBackgroundColor(Wt::WColor("#8B0000")); //add background color
	itext->decorationStyle().setForegroundColor(Wt::WColor("#FFFFFF")); //add forerground(text) color
	itext->decorationStyle().setCursor(Wt::Cursor::PointingHand); //add cursor style
	addtext1(container); //call function to add additional text
}

template<typename a>
void intro::addtext1(a& container) //template function definition
{
	ptext = new Wt::WText *[size(txt)]; //dynamic array of pointer initialization
	container->decorationStyle().setForegroundColor(Wt::WColor("#FFFFFF")); //add foreground(text) color
	for (int i = 0; i < size(txt); i++) {
		ptext[i] = container->addWidget(Wt::cpp14::make_unique<Wt::WText>(txt[i])); //add text widget to container (ptext)
		ptext[i]->setStyleClass("reactive text-center"); //add classes to ptext
		ptext[i]->decorationStyle().setBackgroundColor(Wt::WColor(col[i])); //add background color
		ptext[i]->decorationStyle().setCursor(Wt::Cursor::PointingHand); //add cursor style
	}
}

intro::intro(string image) {
	this->image = image; //parameterized initialization
}

intro::~intro() {
	delete[] ptext; //delete dynamic array of ptext
}

template<typename a>
void intro::addimage(a& container) {
	img = container->addWidget(Wt::cpp14::make_unique<Wt::WImage>(Wt::WLink(image))); //add image to the widget
	img->setAlternateText("Main Image"); //set alterntive text for image
	img->setStyleClass("img-responsive"); //add responsive class to image
	img->setMargin("30px", Wt::Side::Top); //add margin to top
	img->setWidth("100%"); //set image width
	img->setHeight("100%"); //set image height
	img->decorationStyle().setCursor(Wt::Cursor::PointingHand); //add cursor design to image
	container->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000)); //add animation on load
	addtext(container); //call function to add text
}

void intro::checkfiles() {
	string a,h;
	fstream fs;
	fs.open("files/recipe_num.txt", ios::in); //open file to check recipe numbers
	fs >> u; //get the file data as string
	fs.close();//close the opened file
	fs.open("files/user_recipe_num.txt", ios::in); //file to check users number
	fs >> a;
	stringstream ss(a);
	vector<string> m;
	while (getline(ss, h, ',')) { //separate by ",'
		m.push_back(h);
	}
	v = to_string(size(m)); //get no. of users
	fs.close();
}

auto intro::makeintro() {
	auto container = Wt::cpp14::make_unique<Wt::WContainerWidget>(); //add container widget
	container->setId("i");//declare id to the container
	addimage(container); //call function to add image
	return container; //return container to the main file
}

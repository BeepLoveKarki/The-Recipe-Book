#pragma once
#include "modal.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <Wt/WEnvironment.h>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WTextArea.h>
#include <Wt/WWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLabel.h>
#include <Wt/WPushButton.h>
#include <Wt/WBreak.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WFileUpload.h>
#include <Wt/WRegExpValidator.h>
#include <Wt/WAnimation.h>
#include <Windows.h>
#include <WinBase.h>
#include <time.h>

using namespace std;

class form{
public:
	int find;
	form(); //constructor declaration
	~form() {}; //destructor declaration
	template<typename T> Wt::WPushButton* showform(T&,string); // function to show form box
	string give(wstring); //function to convert wstring to strring
	vector <Wt::WLabel*> labels; //vector of lables
	vector <Wt::WLineEdit*> boxes; //vector of boxes
	vector <Wt::WTextArea*> texts; //text area for ingredients
	vector <Wt::WBreak*> b; //line break vectors
	Wt::WPushButton* button, *bull, *done, *cancel; //button class for file upload
	int decide; //button to decide what
	string fr[6]; //string to hold values
private:
	string m; //random id
	string em; //string to hold email
	fstream fs; //file handling stream declaration
	Wt::WFileUpload *fu; //file upload widget
	template<typename T> void addingredients(T& form);// function declaration to add ingredients
	template<typename T> void adddescription(T& form);// function declaration to add description
	template<typename T> void addsteps(T& form);// function declaration to add steps
	template<typename T> void addlabel(T& form, string data); //function to add label
	template<typename T> void addfield(T& form); //function to add field
	template<typename T> void addmedia(T& form); //function to add image
	template<typename T> void addit(T&); //function to submit
	void writetofile(); //function to handle files
	void addnum(); //function to add 1 to number of recipe
	void uploadfile(); //function to upload file
	void add_data();//function to add data of recipe
	string see_data(); //function to see all data present
	unique_ptr<Wt::WLabel> makelabel(string data); //function to return label design
	unique_ptr<Wt::WLineEdit> makebox(); //function to return fieldbox design
	int a;
};


form::form() {
	find = -1;
	srand(time(NULL)); //random seed
	m = to_string(rand() % (10000 - 1000 + 1) + 1000); //random id generation
}

template<typename T>
Wt::WPushButton* form::showform(T& form,string email) { //function to show form
	find++;
	em = email; //assign email incomin to the one in this class
	if (decide == 0) {
		addlabel(form, "Enter Recipe Name");//label for name of recipe
	}
	if (decide == 1) {
		addlabel(form, "Recipe Name");//label for name of recipe
	}
	addfield(form); //field for name of recipe
	adddescription(form); //call function to add description
	addingredients(form); //call function to add ingredients
	addsteps(form); //call function to add steps
	addmedia(form); //call function to add image
	addit(form); //call function to add submission
	for (auto& b: boxes) {
		b->setWidth("60%"); //set width of input field
		b->setStyleClass("input-lg text-center center-block"); //add style class to input fiesld
		b->setAttributeValue("required", ""); //set required attribute to true
		b->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000));//add animation on load
	}
	if (decide == 1) { //set edit text
		for (int i = 3; i < 5; i++) {
			while (fr[i].find("<br/>") != string::npos) {
				fr[i].replace(fr[i].find("<br/>"),5,"\n"); //replace all <br/> by \n
			}
		}
		boxes.at(0)->setText(fr[1]);
		boxes.at(1)->setText(fr[2]);
		boxes.at(2)->setText(fr[5]);
		texts.at(0)->setText(fr[3]);
		texts.at(1)->setText(fr[4]);
	}
	for (auto& t:texts) {
		t->setColumns(40); //set columns for text-area
		t->setRows(7); //set rows for text-area
		t->setWidth("60%"); //set width of text-area
		t->addStyleClass("center-block text-center input-lg"); //add style classes to text-area;
		t->setAttributeValue("required", ""); //set required attribute to true
		t->animateShow(Wt::WAnimation::WAnimation(Wt::AnimationEffect::SlideInFromLeft, Wt::TimingFunction::Linear, 1000)); //add animation on load
	}
	labels.at(0)->setMargin("30px", Wt::Side::Top); //add margin to top
	return cancel;
}

template<typename T>
void form::addingredients(T& form) {
	b.push_back(form->addWidget(Wt::cpp14::make_unique <Wt::WBreak>())); //add line break
	if (decide == 0) {
		addlabel(form, "Enter ingredients one per line (Include amount within brackets)"); //label for ingredients
	}
	if (decide == 1) {
		addlabel(form, "Ingredients"); //label for ingredients
	}
	texts.push_back(form->addWidget(Wt::cpp14::make_unique<Wt::WTextArea>())); //add text are for ingredients
}

template<typename T>
void form::adddescription(T& form) {
	b.push_back(form->addWidget(Wt::cpp14::make_unique <Wt::WBreak>())); //add line break
	if (decide == 0) {
		addlabel(form, "Enter Description"); //label for description
	}
	if (decide == 1) {
		addlabel(form, "Description"); //label for description
	}
	addfield(form); //field for description
}

template<typename T>
void form::addsteps(T& form) {
	b.push_back(form->addWidget(Wt::cpp14::make_unique <Wt::WBreak>())); //add line break
	if (decide == 0) {
		addlabel(form, "Enter steps one per line (Make as short as possible)"); //label for ingredients
	}
	if (decide == 1) {
		addlabel(form, "Steps"); //label for ingredients
	}
	texts.push_back(form->addWidget(Wt::cpp14::make_unique<Wt::WTextArea>())); //add text are for steps
	if (decide == 0) {
		addlabel(form, "Enter Creditor's Name"); //label for name
	}
	if (decide == 1) {
		addlabel(form, "Creditor's Name"); //label for name
	}
	addfield(form); //box for name
}

template<typename T>
void form::addmedia(T& form) {
	b.push_back(form->addWidget(Wt::cpp14::make_unique <Wt::WBreak>())); //add line break
	form->addWidget(Wt::cpp14::make_unique <Wt::WBreak>()); //add line break
	if (decide == 0) {
		button = form->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Upload Your Recipe Photo")); //button to upload photo
		button->setStyleClass("btn btn-lg btn-danger"); //set button style class
	}
	if (decide == 1) {
		button = form->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Edit Your Recipe Photo")); //button to upload photo
		button->setStyleClass("btn btn-lg btn-success"); //set button style class
	}
	fu =form->addWidget(Wt::cpp14::make_unique<Wt::WFileUpload>()); //file upload widget declaration
	fu->setId("forme"); //setid to widget
	fu->setFilters("image/*"); //accept only images
	fu->setHidden(true);//hide it
	button->setAttributeValue("onclick", "document.getElementById('informe').click()");//add on click attribute
}

template<typename T>
void form::addit(T& form) {
	b.push_back(form->addWidget(Wt::cpp14::make_unique <Wt::WBreak>())); //add line break
	b.push_back(form->addWidget(Wt::cpp14::make_unique <Wt::WBreak>())); //add line break
	b.push_back(form->addWidget(Wt::cpp14::make_unique <Wt::WBreak>())); //add line break
	if (decide == 0) {
		done = form->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Upload")); //button to submit
		cancel = form->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Cancel")); //button to cancel
	}
	if (decide == 1) {
		done = form->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Update")); //button to submit
	    cancel = form->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Cancel")); //button to cancel
		form->addWidget(Wt::cpp14::make_unique<Wt::WBreak>()); //add line break
		bull = form->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Delete this recipe")); //button to upload photo
		bull->setMargin("20px", Wt::Side::Top);
		bull->setStyleClass("btn btn-lg btn-primary"); //set button style class
		bull->clicked().connect([=] {
			string d = "uploads/" + fr[0] + ".jpg",e; //path to move uploaded file to our folder
			string g = see_data();
			string f = g;
			f.erase(0, f.find(fr[0]));
			int a = f.substr(0, f.find_first_of("!")).length();
			g.erase(g.find(fr[0]), a+1);
			fs.open("files/recipe/" + em + ".txt", ios::out); //open file for overwriting
			fs << g; //write to file
			fs.close();
			fs.open("files/recipe_num.txt",ios::in);
			fs >> e;
			fs.close();
			fs.open("files/recipe_num.txt", ios::out);
			fs << to_string(stoi(e) - 1);
			fs.close();
			if (DeleteFile(wstring(d.begin(), d.end()).c_str())) {
				modal mo("Recipe Deleted", "<p>Your Recipe has been deleted!!! You will now not find it in <b>Recipe List</b> area!!! </p>"); //instance of modal class
				mo.showdialog(); //show dialog
			}//delete image
		});
	}
	done->setStyleClass("btn btn-lg btn-info"); //set button style class
	cancel->setStyleClass("btn btn-lg btn-warning"); //set button style class
	cancel->setMargin("5px", Wt::Side::Left); //add margin to left
	done->clicked().connect([=] {
		int y = 0; //stack variable
		for (auto& b : boxes) {
			if (give(b->text()).length() == 0) {
				b->setFocus(); //set focus if empty
				b->setPlaceholderText("Please enter this field!!!"); //show placeholder to input
			}
			else {
				y++; //increase stack variable by 1
			}
		}
		for (auto& t : texts) {
			if (give(t->text()).length() == 0) {
				t->setFocus(); //set focus if empty
				t->setPlaceholderText("Please enter this field!!!"); //show placeholder to input
			}
			else {
				y++; //increase stack variable by 1
			}
		}
		if (y == 5)
			uploadfile(); //call uploadfile if the stack variable becomes 5
	});
}

void form::uploadfile() {
	fu->upload();
	fu->uploaded().connect([=] { //on getting upload call it
		    string c = fu->spoolFileName(); //get upload file name
			string d= "uploads/" + m + ".jpg"; //path to move uploaded file to our folder
			string e= "uploads/" + fr[0] + ".jpg"; //path to move uploaded file to our folder
			if (decide == 1) {
				DeleteFile(wstring(e.begin(), e.end()).c_str()); //delete previous image
			}
			if (c.length() != 0) {
				if (MoveFile(wstring(c.begin(), c.end()).c_str(), wstring(d.begin(), d.end()).c_str())) { //move uploaded file
					writetofile(); //write data to file
				}
			}
			else {
				writetofile(); //write to file
			}
		});
}

void form::writetofile() {
	if (decide == 0) {
		string l;
		fs.open("files/user_recipe_num.txt", ios::in); //open file to read
		fs >> l; //read from file
		if (l.find(em) != string::npos) { //check if email exists in the file
			fs.close(); //close file
			addnum(); //call function to add number of recipe
			add_data(); //call function to add data
		}
		else {
			fs.close();
			fs.open("files/user_recipe_num.txt", ios::app); //open file in append mode
			fs << em + ","; //append to file
			fs.close(); //close file
			fs.open("files/recipe/" + em + ".txt", ios::out); //open file in write mode
			fs.close();
			addnum();
			add_data();
		}
	}
	if (decide == 1) {
		add_data();
	}
}

void form::add_data() {
    fs.open("files/recipe/" + em + ".txt", ios::app); //open file for appending
	string oi[5] = {give(boxes.at(0)->text()),give(boxes.at(1)->text()),give(texts.at(0)->text()),give(texts.at(1)->text()),give(boxes.at(2)->text())};
	for (int i = 0; i < 5; i++) {
		while (oi[i].find("\n") != string::npos) { //check all '\n' characters
			oi[i].replace(oi[i].find("\n"), 1, "<br/>"); //replace all '\n' with '<br/>'
		}
		while (oi[i].find(",") != string::npos) { //check all '@' characters
			oi[i].replace(oi[i].find(","), 1, "@"); //replace all ',' with '@'
		}
	}
	if (decide == 1) {
		fs.close();
		string g = see_data(); //get original file string
		string f = g;
		string l = m;
		for (int i = 0; i < 5; i++) { //make new string
			l += ","+oi[i];
		 }
		 l += "!";
		 f.erase(0, f.find(fr[0]));
		 a = f.substr(0, f.find_first_of("!")).length();
		 g.replace(g.find(fr[0]),a+1,l); //replace the string in file
		 fs.open("files/recipe/" + em + ".txt", ios::out); //open file for overwriting
		 fs << g; //write to file
		 fs.close();

	}
	else {
		fs << m << "," << oi[0] << "," << oi[1] << "," << oi[2] << "," << oi[3] << "," << oi[4] << "!"; //append to file
		fs.close();
	}
	if (decide == 0) {
		modal mo("Recipe Added", "<p>Your Recipe has been added!!! It will be now visible in <b>Recipe List</b> area!!! </p>"); //instance of modal class
		mo.showdialog(); //show dialog
	}
	if (decide == 1) {
		modal mo("Recipe Updated", "<p>Your Recipe has been updated!!! You may check it in <b>Recipe List</b> area!!! </p>"); //instance of modal class
		mo.showdialog(); //show dialog
	}
}

string form::see_data() {
	stringstream ss,buffer;
	string a;
	fs.open("files/recipe/" + em + ".txt", ios::in); //open file for reading
	buffer.str("");
	buffer << fs.rdbuf();
	string contents(buffer.str());
	a.append(contents);
	fs.close();
	return a;
}

void form::addnum() {
	string a;
	fs.open("files/recipe_num.txt", ios::in); //open file in read mode
	fs >> a; //read from file
	fs.close(); 
	fs.open("files/recipe_num.txt", ios::out); //open same file in write mode
	fs <<to_string(stoi(a)+1) ; //write to the file
	fs.close();
}

template<typename T>
void form::addlabel(T& form, string text) {
	labels.push_back(form->addWidget(makelabel("<h4>"+text+"</h4>"))); //add label to form fields
}

template<typename T>
void form::addfield(T& form) {
	boxes.push_back(form->addWidget(makebox())); //add fields
}

unique_ptr<Wt::WLabel> form::makelabel(string data) {
	return Wt::cpp14::make_unique<Wt::WLabel>(data); //return label
}

unique_ptr<Wt::WLineEdit> form::makebox() {
	return Wt::cpp14::make_unique<Wt::WLineEdit>(); //return field
}

string form::give(wstring s) {
	string f;
	for (char x : s)
		f += x; //append wstring cgar to string
	return f;
}






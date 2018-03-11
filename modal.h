#pragma once
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WMessageBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <string>

class modal {
public:
	modal(string,string); //constructor
	~modal() {}; //destructor
	void showdialog(); //function declaration to show dialog
private:
	string text,head; //sting to hold text
};

modal::modal(string head,string text) {
	this->head = head;
	this->text = text; //parameterized constructor
}

void modal::showdialog() { //functon definition to show dialog
	Wt::StandardButton answer = Wt::WMessageBox::show(head,text,Wt::StandardButton::Ok); //show dialog box
	if (answer==Wt::StandardButton::Ok) {
		Wt::WApplication::instance()->refresh();
		Wt::WApplication::instance()->redirect("/"); //refresh on click
	}
}

#pragma once
#include "form.h"
#include "modal.h"
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WAnimation.h>
#include <Wt/WBreak.h>
#include <Wt/WDialog.h>
#include <Wt/WLabel.h>
#include <Wt/WLineEdit.h>
#include <Wt/WBreak.h>
#include <Wt/Mail/Client>
#include <Wt/Mail/Message>
#include <Windows.h>
#include <wininet.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#pragma comment(lib,"Wininet.lib")

using namespace std;
class emailmodal {
public:
	emailmodal() {}; //constructor declaration
	~emailmodal() {}; //destructor declaration
	void dostuffs(Wt::WObject*,string);
private:
	fstream fd;
	Wt::WDialog* mod0,*mod,*mod1;
	Wt::WPushButton *btn, *btn1,*bt,*bt1;
	Wt::WLineEdit *pass;
	void sendmail(string,Wt::WObject*);
	string a;
};

void emailmodal::dostuffs(Wt::WObject* con,string email) {
	mod0= con->addChild(Wt::cpp14::make_unique<Wt::WDialog>("User not found")); //create a modal
	Wt::WLabel* label = mod0->contents()->addWidget(Wt::cpp14::make_unique<Wt::WLabel>("You aren't registered. Would like to register now?"));// add content
	btn = mod0->footer()->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("OK")); //add push button
	btn->setDefault(true);
	btn1 = mod0->footer()->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Cancel")); //add push button
	btn1->clicked().connect(mod0, &Wt::WDialog::reject); //reject on click
	btn->clicked().connect([=] {
		if (InternetCheckConnection(L"http://www.google.com", FLAG_ICC_FORCE_CONNECTION, 0)) { //check if internet is on
			sendmail(email,con); //send mail on click
		}
		else {
			con->removeChild(mod0);
			mod = con->addChild(Wt::cpp14::make_unique<Wt::WDialog>("No internet connection found")); //create a modal
			Wt::WLabel* label = mod->contents()->addWidget(Wt::cpp14::make_unique<Wt::WLabel>("You are offline. Try again when you get online."));// add content
			bt = mod->footer()->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("OK")); //add push button
			bt->setDefault(true);
			bt->clicked().connect([=] {
				con->removeChild(mod); //remove this modal
			});
			mod->setMovable(false);
			mod->show();
		}
	});
	mod0->setMovable(false);
	mod0->show(); //show modal
}

void emailmodal::sendmail(string email,Wt::WObject* con) {
	srand(time(NULL));
	a = to_string(rand() % (100000 - 10000) + 10000);
	Wt::Mail::Message message;
	message.setFrom(Wt::Mail::Mailbox("booktherecipe@gmail.com", "The Recipe Book")); //add from 
	message.addRecipient(Wt::Mail::RecipientType::To, Wt::Mail::Mailbox(email, "")); //add to
	message.setSubject("Confirmation Code"); //set subject
	message.setBody("Your confirmation code is "+a); //send email
	Wt::Mail::Client client("aspmx.l.google.com"); //client
	client.connect("aspmx.l.google.com",25);
	client.send(message);
	con->removeChild(mod0);
	mod1 = con->addChild(Wt::cpp14::make_unique<Wt::WDialog>("Enter the password")); //create a modal
	Wt::WLabel* label = mod1->contents()->addWidget(Wt::cpp14::make_unique<Wt::WLabel>("Please enter the code we sent to your email!!! Check it in spam folder too!!!"));
	pass = mod1->contents()->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>()); //pass word label
	label->setBuddy(pass);
	pass->setEchoMode(Wt::EchoMode::Password);
	mod1->contents()->addWidget(Wt::cpp14::make_unique<Wt::WBreak>());
	Wt::WText *t = mod1->contents()->addWidget(Wt::cpp14::make_unique<Wt::WText>("Code didn't match!!! Try again!!!"));
	t->setHidden(true);
	bt1 = mod1->footer()->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("OK")); //add push button
	Wt::WPushButton* can = mod1->footer()->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Cancel")); //add push button
	can->clicked().connect([=] {
		mod1->reject(); //hide on click
	});
	bt1->setDefault(true);
	bt1->clicked().connect([=] {
		form f;
		if (f.give(pass->text()) != a) {
			t->setHidden(false);
		}
		else {
			con->removeChild(mod1);
			fd.open("files/user_recipe_num.txt",ios::app);
			fd << email << ",";
			fd.close();
			fd.open("files/recipe/"+email+".txt", ios::out);
			fd.close();
			modal m("User added", "You have been registered!!! Now you may add your recipe");
			m.showdialog();
		}
	});
	mod1->show();
}




# The Recipe Book
# Device Friendly Web Development using C++ 

This is a device friendly website designed completely via C++ with the help of Web Toolkit C++ (WT C++) framework (https://www.webtoolkit.eu/wt). It is a simple web application which fits the screen size across any screen device. It is a website containing platform for openly serving your recipe ideas via your email account!!! It contains around all major features of a website like email regexp regonition, email verification through code, navigation bar,etc. The only difference here is the use of text files instead of database, since this project is created for debug process!!!

This project breaks the general trend of thinking C++ as not a language for web development!!! It makes C++ to speak "I am not as weak you think I am".

Some desktop screenshots of the website created are:

<img src="https://github.com/BeepLoveKarki/The-Recipe-Book/blob/master/Screenshots/ss1.png"/>
<img src="https://github.com/BeepLoveKarki/The-Recipe-Book/blob/master/Screenshots/ss2.png"/>
<img src="https://github.com/BeepLoveKarki/The-Recipe-Book/blob/master/Screenshots/ss3.png"/>
<img src="https://github.com/BeepLoveKarki/The-Recipe-Book/blob/master/Screenshots/ss4.png"/>
<img src="https://github.com/BeepLoveKarki/The-Recipe-Book/blob/master/Screenshots/ss5.png"/>
<img src="https://github.com/BeepLoveKarki/The-Recipe-Book/blob/master/Screenshots/ss6.png"/>
<img src="https://github.com/BeepLoveKarki/The-Recipe-Book/blob/master/Screenshots/ss7.png"/>
<img src="https://github.com/BeepLoveKarki/The-Recipe-Book/blob/master/Screenshots/ss8.png"/>
<img src="https://github.com/BeepLoveKarki/The-Recipe-Book/blob/master/Screenshots/ss9.png"/>
<img src="https://github.com/BeepLoveKarki/The-Recipe-Book/blob/master/Screenshots/ss10.png"/>

Some mobile screenshots of the website created are:

<img src="https://github.com/BeepLoveKarki/The-Recipe-Book/blob/master/Screenshots/ss12.png"/>
<img src="https://github.com/BeepLoveKarki/The-Recipe-Book/blob/master/Screenshots/ss13.png"/>

Steps to run the project are as follows:

1. Install MS Visual Studio (MSVC) 2015 or newer
2. Download the required version of WT C++ framework as per the visual studio
3. Import the project folder to MSVC IDE
4. Right click on the project folder and select 'Properties' option
5. In Configuration Properties -> Debugging, set command arguments to
   --http-address=0.0.0.0 --http-port=8080 --deploy-path=/hello --docroot=.
6. Browse http://localhost:8080/hello



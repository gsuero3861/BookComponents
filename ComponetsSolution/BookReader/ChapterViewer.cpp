#include "pch.h" 

using namespace BookReader;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

ChapterViewer::ChapterViewer()
{
	initelements();
}

void ChapterViewer::initelements()
{
	this->_elementspanel =  ref new StackPanel();
	this->Children->Append(_elementspanel);
	this->_elementspanel->Orientation = Orientation::Horizontal ;	
	this->_textelement =  ref new TextView();
	this->_videoelement =  ref new VideoView();
	this->_pageselement =  ref new StackView(); 
	this->_galleryelement =  ref new StackView();
	this->_elementspanel->Children->Append(this->_textelement);
	this->_elementspanel->Children->Append(this->_pageselement);
	this->_elementspanel->Children->Append(this->_videoelement);
	this->_elementspanel->Children->Append(this->_galleryelement);
}

void ChapterViewer::LoadBook()
{
	 
}
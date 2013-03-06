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

DynamicBackground::DynamicBackground()
{
	this->_backgroundcontainer = ref new StackPanel();
	this->_backgroundcontainer->Background = ref new SolidColorBrush(Windows::UI::Colors::Transparent);
	this->Children->Append(this->_backgroundcontainer);
	this->_backgroundcontainer->Orientation =  Orientation::Horizontal ;
	this->_backgroundwidth = 0.0 ;
	this->_itemheight = 0.0 ;
	this->_itemwidth =  0.0 ;
	this->_numberofitems = 0 ; 

}

void DynamicBackground::setbackgroundsize()
{
	if(this->_itemheight > 0  && this->_itemwidth >0 )
	{
		int32 _newnumberofitems = (int32)ceil(this->_backgroundwidth / _itemwidth); 
		for (int i = this->_numberofitems  ; i < _newnumberofitems; i++)
		{
			Image ^ tmpimg =  ref new Image();
			tmpimg->Width = this->_itemwidth ;
			tmpimg->Height =  this->_itemheight ;
			tmpimg->Source = this->_backgroundsource ;
			
			this->_backgroundcontainer->Children->Append(tmpimg);
		}
		for (int i = _newnumberofitems ; i < this->_numberofitems; i++)
		{
			this->_backgroundcontainer->Children->RemoveAtEnd();
		}
	}
}
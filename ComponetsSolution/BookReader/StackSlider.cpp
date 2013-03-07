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

StackSlider::StackSlider()
{
	initstackscontrols();
	initslidercontrols();

}

#pragma region Stacks

void StackSlider::initstackscontrols()
{
	this->_gridstacks = ref new Grid(); 

	this->_itemsscroll =  ref new ScrollViewer();
	this->_itemsscroll->HorizontalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Enabled ;
	this->_itemsscroll->HorizontalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Hidden;
	this->_itemsscroll->VerticalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Disabled ; 
	this->_itemsscroll->VerticalScrollBarVisibility = Windows::UI::Xaml::Controls::ScrollBarVisibility::Disabled;
	this->_gridstacks->Children->Append(this->_itemsscroll);

	this->_itemspanel = ref new StackPanel() ;
	this->_itemspanel->Orientation = Orientation::Horizontal;
	this->_itemspanel->Background = ref new SolidColorBrush(Windows::UI::Colors::Transparent);
	this->_itemspanel->ManipulationMode = ManipulationModes::All; 

	this->_itemsscroll->Content = this->_itemspanel ;
 
}

#pragma endregion


#pragma region Slider

void StackSlider::initslidercontrols()
{
	this->_gridslider =  ref new Grid(); 	 
}

void StackSlider::loadstacks() 
{
	for (int i = 0; i < _datasource->Size; i++)
	{
		StackView^ Stackview1 = ref new StackView();
		Stackview1->StackViewItemHeight = this->_stackitemheight ;
		Stackview1->StackViewItemWidth = this->_stackitemwidth ;
		Stackview1->DeltaItemSeparation = 40 ;
		Stackview1->FullScreenX = 50 ;
		Stackview1->FullScreenY = 0.0 ;
		Stackview1->FullSreenItemHeight = 768 ;
		Stackview1->FullSreenItemWidth  = 1024;  
		Stackview1->DataSource = _datasource->GetAt(i);
		//Stackview1->Width = 2*this->_stackitemwidth ;

	}
}

#pragma endregion
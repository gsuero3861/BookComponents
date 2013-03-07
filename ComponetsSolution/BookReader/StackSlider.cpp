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
	//init the current stack and its current item
	this->_currentstack = 0 ;
	this->_currentstackitem = 0 ;

	this->_gridstacks = ref new Grid(); 
	this->Children->Append(this->_gridstacks);

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

void StackSlider::loadstacks() 
{
	for (int i = 0; i < _datasource->Size; i++)
	{
		StackView^ Stackview1 = ref new StackView();
		Stackview1->StackNumber = i ;
		Stackview1->StackViewItemHeight = this->_stackitemheight ;
		Stackview1->StackViewItemWidth = this->_stackitemwidth ;
		Stackview1->StackViewMargin = 100 ;
		Stackview1->DeltaItemSeparation = 40 ;
		Stackview1->FullScreenX = 50 ;
		Stackview1->FullScreenY = 0.0 ;
		Stackview1->FullSreenItemHeight = 768 ;
		Stackview1->FullSreenItemWidth  = 1024;  
		Stackview1->DataSource = _datasource->GetAt(i); 
		this->_itemspanel->Children->Append(Stackview1);
		Stackview1->StackManipulationStarted += ref new StackManipulationStartedEventHandler(this, &BookReader::StackSlider::StackManipulationStarted_1);
		Stackview1->StackManipulationFinished += ref new StackManipulationFinishedEventHandler(this, &BookReader::StackSlider::StackManipulationFinished_1);
		Stackview1->StackAnimationCompleted += ref new StackAnimationCompletedEventHandler(this,&BookReader::StackSlider::StackAnimationCompleted_1);
	}
}

void BookReader::StackSlider::StackManipulationStarted_1(Platform::Object ^ sender , int32 args)
{

}
	
void BookReader::StackSlider::StackManipulationFinished_1(Platform::Object ^ sender , int32 stacknumber, int32 citem) 
{

}

void BookReader::StackSlider::StackAnimationCompleted_1(Platform::Object ^ sender , int32 stacknumber)
{

}


#pragma endregion


#pragma region Slider

void StackSlider::initslidercontrols()
{
	this->_gridslider =  ref new Grid(); 	 
}



#pragma endregion
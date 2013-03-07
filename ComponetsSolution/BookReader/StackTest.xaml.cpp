//
// StackTest.xaml.cpp
// Implementation of the StackTest class
//

#include "pch.h"
#include "StackTest.xaml.h"

using namespace BookReader;
using namespace BookReader::BookData;

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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

StackTest::StackTest()
{
	InitializeComponent();
	loaddata() ;
	
	Platform::Collections::Vector<StackDataSource ^> ^ _datasource =  ref new Platform::Collections::Vector<StackDataSource ^>();
	_datasource->Append(stack1);
	_datasource->Append(stack2);
	this->_stackslider1->DataSource = _datasource ;
	/**
	Stackview1->StackViewItemHeight = 300.0 ;
	Stackview1->StackViewItemWidth = 400.0 ;
	Stackview1->DeltaItemSeparation = 40 ;
	Stackview1->FullScreenX = 50 ;
	Stackview1->FullScreenY = 0.0 ;
	Stackview1->FullSreenItemHeight = 768 ;
	Stackview1->FullSreenItemWidth  = 1024;  
	this->Stackview1->DataSource = stack1 ; 

	slider1->ItemHeight = 768 ;
	slider1->ItemWidth = 1024 ;
	slider1->ControlHeight = 768 ;
	slider1->ControlWidth = 1366 ;
	slider1->MinScale = 0.9 ;
	slider1->CurrentItem = 5 ;
	slider1->MediumPaths = paths1 ; */
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void StackTest::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Unused parameter
}

void StackTest::loaddata()
{

	paths1 =  ref new  Platform::Collections::Vector<Platform::String^> ();	
	for (int i = 0; i < 16; i++)
		paths1->Append("ms-appx:///images/img"+ i +".jpg") ;
		
	stack1 = ref new  StackDataSource();
	stack1->ThumbsList = paths1 ;
	stack1->MediumList = paths1 ;
	stack1->FullPageList = paths1 ;

	paths2 =  ref new  Platform::Collections::Vector<Platform::String^> ();	
	for (int i = 15; i >= 0; i--)
		paths2->Append("ms-appx:///images/img"+ i +".jpg") ;
		
	stack2 = ref new  StackDataSource();
	stack2->ThumbsList = paths2;
	stack2->MediumList = paths2 ;
	stack2->FullPageList = paths2 ;
}


 
 
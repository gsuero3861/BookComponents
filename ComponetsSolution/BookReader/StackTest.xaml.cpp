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
	slider1->ItemHeight = 768 ;
	slider1->ItemWidth = 1024 ;
	slider1->ControlHeight = 768 ;
	slider1->ControlWidth = 1366 ;
	slider1->MinScale = 0.9 ;
	slider1->CurrentItem = 5 ;
	slider1->MediumPaths = paths1 ;
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
		
	StackDataSource ^ stack1 = ref new  StackDataSource();
	stack1->ThumbsList = paths1 ;
	stack1->MediumList = paths1 ;
	stack1->FullPageList = paths1 ;
}

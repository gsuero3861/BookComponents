//
// TestPage.xaml.cpp
// Implementation of the TestPage class
//

#include "pch.h"
#include "TestPage.xaml.h"

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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

TestPage::TestPage()
{
	InitializeComponent();  
	loadbook1();
	 
	//loadbook1();
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void TestPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Unused parameter
}


void TestPage::loadbook1()
{
	this->_book1 =  ref new BookData::BookDataSource();
	paths1 =  ref new  Platform::Collections::Vector<Platform::String^> ();	
	for (int i = 0; i < 16; i++)
		paths1->Append("ms-appx:///images/img"+ i +".jpg");

	paths2 =  ref new  Platform::Collections::Vector<Platform::String^> ();	
	for (int i = 15; i >= 0 ; i--)
		paths2->Append("ms-appx:///images/img"+ i +".jpg");

	BookData::StackDataSource ^ stack1 = ref new BookData::StackDataSource();
	stack1->ThumbsList = paths1 ;
	stack1->MediumList = paths1 ;
	stack1->FullPageList = paths1 ;

	BookData::StackDataSource ^ stack2 = ref new BookData::StackDataSource();
	stack2->ThumbsList = paths2 ;
	stack2->MediumList = paths2 ;
	stack2->FullPageList = paths2 ;


	BookData::ChapterDataSource^ chapter1 = ref new BookData::ChapterDataSource();
	chapter1->Title = "Chapter 1" ;
	chapter1->Text = ref new BookData::TextDataSource();
	chapter1->Video = ref new BookData::VideoDataSource();
	chapter1->Pages = stack1 ;
	chapter1->Gallery = stack2 ;

	BookData::ChapterDataSource^ chapter2 = ref new BookData::ChapterDataSource();
	chapter1->Title = "Chapter 2" ;
	chapter1->Text = ref new BookData::TextDataSource();
	chapter1->Video = ref new BookData::VideoDataSource();
	chapter1->Pages = stack2 ;
	chapter1->Gallery = stack1 ;

	Platform::Collections::Vector<BookData::ChapterDataSource ^>^ _chapters = ref new Platform::Collections::Vector<BookData::ChapterDataSource ^>();
	_chapters->Append(chapter1);
	_chapters->Append(chapter2);

	this->_book1 ->Title = "BOOK 1" ;
	this->_book1->Chapters = _chapters ; 	
	this->_book1->BackgroundSource = "ms-appx:///images/background.png" ;

 	this->bookviewer1->DataSource = this->_book1 ;
}
//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

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

MainPage::MainPage()
{
	InitializeComponent();
	paths =  ref new  Platform::Collections::Vector<Platform::String^> ();
	
	for (int i = 0; i < 16; i++)
	{
		paths->Append("ms-appx:///images/img"+ i +".jpg");
	}	 
	
	this->_dynaminc01 ->SourcePath = paths->GetAt(2);
	this->_dynaminc01 ->BackgroundWidth = 1850 ;

	//loadbook1();
	//this->_chaptertest1->PagesThumbList = paths ;
	 /**
	BookData::StackDataSource ^ sdata = ref new BookData::StackDataSource();
	sdata->ThumbsList = paths ;
	sdata->MediumList = paths ;
	sdata->FullPageList = paths ;

	BookData::ChapterDataSource^ bsource = ref new BookData::ChapterDataSource();
	bsource->Title = "" ;
	bsource->Text = ref new BookData::TextDataSource();
	bsource->Video = ref new BookData::VideoDataSource();
	bsource->Pages = sdata ;
	bsource->Gallery = sdata ;
	this->_chaptertest1->DataSource = bsource ;
	this->_chaptertest1->ThumbPageHeight = 300.0 ;
	this->_chaptertest1->ThumbPageWidth = 400.0 ;
	this->_chaptertest1->ThumbPageSeparation = 40 ;
	this->_chaptertest1->PageHeight = 768 ;
	this->_chaptertest1->PageWidth ;
	this->_chaptertest1->PageTranslationX = 0.0 ;
	this->_chaptertest1->PageTranslationY = 0.0 ;
	this->_chaptertest1->PageHeight =  768 ;
	this->_chaptertest1->PageWidth = 1024 ; 

	this->_chaptertest1->ThumbGalleryHeight = 300 ;
	this->_chaptertest1->ThumbGalleryWidth = 400.0 ;
	this->_chaptertest1->ThumbGallerySeparation = 40 ;
	this->_chaptertest1->GalleryHeight = 768 ;
	this->_chaptertest1->GalleryWidth = 1024 ;
	this->_chaptertest1->GalleryTranslationX = 0.0 ;
	this->_chaptertest1->GalleryTranslationY = 0.0 ;
	this->_chaptertest1->GalleryHeight =  768 ;
	this->_chaptertest1->GalleryWidth = 1024 ;   
	 
	stackview1->StackViewItemHeight = 300.0 ;
	stackview1->StackViewItemWidth = 400.0 ;
	stackview1->DeltaItemSeparation = 40 ;
	stackview1->FullScreenX = 50 ;
	stackview1->FullScreenY = 0.0 ;
	stackview1->FullSreenItemHeight = 768 ;
	stackview1->FullSreenItemWidth  = 1024;  
	stackview1->DataSource = sdata ;
	
	

	/**
	slider1->ItemHeight = 768 ;
	slider1->ItemWidth = 1024 ;
	slider1->ControlHeight = 768 ;
	slider1->ControlWidth = 1366 ;
	slider1->MinScale = 0.9 ;
	slider1->CurrentItem = 5 ;
	slider1->MediumPaths = paths ;*/
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Unused parameter
}

void MainPage::loadbook1()
{
	this->_book1 =  ref new BookData::BookDataSource();
	Platform::Collections::Vector<Platform::String^>^ paths1 =  ref new  Platform::Collections::Vector<Platform::String^> ();	
	for (int i = 0; i < 16; i++)
		paths1->Append("ms-appx:///images/img"+ i +".jpg");

	Platform::Collections::Vector<Platform::String^>^ paths2 =  ref new  Platform::Collections::Vector<Platform::String^> ();	
	for (int i = 15; i >= 0 ; i++)
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
	//_chapters->Append(chapter1);
	//_chapters->Append(chapter2);

	this->_book1 ->Title = "BOOK 1" ;
	this->_book1->Chapters = _chapters ; 	
	this->_book1->BackgroundSource = "ms-appx:///images/background.png" ;

	this->bookviewer1->DataSource = this->_book1 ;
}


void BookReader::MainPage::Grid_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{
	this->trans1->TranslateX += e->Delta.Translation.X;
	//this->trans1->TranslateY += e->Delta.Translation.Y;
}


void BookReader::MainPage::Grid_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e)
{
	//e->TranslationBehavior =ref new InertiaTranslationBehavior();
	
	//e->TranslationBehavior->DesiredDisplacement = 300 ;
	e->TranslationBehavior->DesiredDeceleration = 500.0 * 96.0 / (1000.0*1000.0) ;
}


void BookReader::MainPage::Grid_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e)
{
	//this->trans1->TranslateX =0 ;
	//this->trans1->TranslateY =0;
}


void BookReader::MainPage::Grid_Tapped_1(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	this->parentransform->TranslateX -= 500;
	this->trans1->TranslateX += 500 ;
}


void BookReader::MainPage::ToggleSwitch_Toggled_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ToggleSwitch ^_ts = (ToggleSwitch^)sender ;
	if(_ts != nullptr )
	{
		if(_ts->IsOn)
		{
			progress1->IsActive = true;
			progress1->Visibility =  Windows::UI::Xaml::Visibility::Visible;
        }
        else
        {
            progress1->IsActive = false;
            progress1->Visibility = Windows::UI::Xaml::Visibility::Collapsed ;
         }
	}
}

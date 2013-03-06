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

BookViewer::BookViewer()
{ 
	initcontrols();
}


void BookViewer::initcontrols()
{
	this->_contentpanel = ref new StackPanel();
	this->_contentpanel->Orientation = Orientation::Horizontal ;
	this->_contentpanel->Background =ref new SolidColorBrush(Windows::UI::Colors::Transparent);
	this->_contentpanel->ManipulationMode = ManipulationModes::All;
	this->_contentpanelscroll =  ref new ScrollViewer();
	this->_contentpanelscroll->HorizontalScrollBarVisibility = ScrollBarVisibility::Hidden ;
	this->_contentpanelscroll->HorizontalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Enabled ;
	this->_contentpanelscroll->VerticalScrollBarVisibility = ScrollBarVisibility::Hidden ;
	this->_contentpanelscroll->VerticalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Disabled ;
	this->_contentpanelscroll->Content = this->_contentpanel ;
	this->_contentpaneltransform = ref new CompositeTransform();
	this->_contentpanel->RenderTransform =  this->_contentpaneltransform ;
	this->_contentpanel->Background = ref new SolidColorBrush(Windows::UI::Colors::Red);

	this->_contentpanel->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, &BookReader::BookViewer::ContentPanel_ManipulationDelta_1);
	this->_contentpanel->ManipulationCompleted += ref new ManipulationCompletedEventHandler(this, &BookReader::BookViewer::ContentPanel_ManipulationCompleted_1);

	this->_backgroundpanel= ref new StackPanel();
	this->_backgroundpanel->Orientation = Orientation::Horizontal ;
	this->_backgroundpanel->Background =ref new SolidColorBrush(Windows::UI::Colors::Black);
	this->_backgroundpanel->ManipulationMode = ManipulationModes::All;
	this->_backgroundpanelscroll =  ref new ScrollViewer();
	this->_backgroundpanelscroll->HorizontalScrollBarVisibility = ScrollBarVisibility::Hidden ;
	this->_backgroundpanelscroll->HorizontalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Enabled ;
	this->_backgroundpanelscroll->VerticalScrollBarVisibility = ScrollBarVisibility::Hidden ;
	this->_backgroundpanelscroll->VerticalScrollMode = Windows::UI::Xaml::Controls::ScrollMode::Disabled ;
	this->_backgroundpanelscroll->Content = this->_backgroundpanel ;
	this->_backgroundpaneltransform = ref new CompositeTransform();
	this->_backgroundpanel->RenderTransform =  this->_backgroundpaneltransform ;

	this->_dynamicbackground =  ref new DynamicBackground();
	this->_backgroundpanel->Children->Append(this->_dynamicbackground);

	this->Children->Append(this->_backgroundpanel);
	this->Children->Append(this->_contentpanel);
	 
	Binding ^ _panelbinding = ref new Binding();
	_panelbinding->Source = _contentpaneltransform ; // myscrollviewer -> nombre del scroll 
	_panelbinding->Path = ref new PropertyPath( "TranslateX" );
	_panelbinding->ElementName = "_contentpaneltransform" ;
	_panelbinding->Converter = ref new  ParallaxConverter() ;	
	BindingOperations::SetBinding((CompositeTransform^)_backgroundpanel->RenderTransform,CompositeTransform::TranslateXProperty,_panelbinding);

}

void BookViewer::loaddata()
{
	for (int i = 0; i < this->_datasource->Chapters->Size ; i++)
	{//llenamos lo chapters del book
		ChapterViewer^ chtmp = ref new ChapterViewer();
		
		//Datos Temporales
		chtmp->ThumbPageHeight = 300.0 ;
		chtmp->ThumbPageWidth = 400.0 ;
		chtmp->ThumbPageSeparation = 40 ;
		chtmp->PageHeight = 768 ;
		chtmp->PageWidth = 1024;
		chtmp->PageTranslationX = 0.0 ;
		chtmp->PageTranslationY = 0.0 ;
		chtmp->PageHeight =  768 ;
		chtmp->PageWidth = 1024 ; 

		chtmp->ThumbGalleryHeight = 300 ;
		chtmp->ThumbGalleryWidth = 400.0 ;
		chtmp->ThumbGallerySeparation = 40 ;
		chtmp->GalleryHeight = 768 ;
		chtmp->GalleryWidth = 1024 ;
		chtmp->GalleryTranslationX = 0.0 ;
		chtmp->GalleryTranslationY = 0.0 ;
		chtmp->GalleryHeight =  768 ;
		chtmp->GalleryWidth = 1024 ;   
		//Asignamos la data
		chtmp->DataSource = this->_datasource->Chapters->GetAt(i) ;
		this->_contentpanel->Children->Append(chtmp);	

	}

	///Llenado del background
	this->_dynamicbackground->SourcePath = this->_datasource->BackgroundSource ;
	this->_dynamicbackground->ItemWidht = 1024 ;
	this->_dynamicbackground->ItemHeight = 768 ;

}


void BookReader::BookViewer::ContentPanel_ManipulationStarted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ e)
{}
	
void BookReader::BookViewer::ContentPanel_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e)
{}
	
void BookReader::BookViewer::ContentPanel_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{
	this->_contentpaneltransform->TranslateX += e->Delta.Translation.X ;
}
	
void BookReader::BookViewer::ContentPanel_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{}
	
void BookReader::BookViewer::ContentPanel_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{}
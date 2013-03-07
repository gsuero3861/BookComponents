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




StackView::StackView()
{
	initstackview();
	initvariables();

	_stackviewitemwidth = 40 ;
	_stackviewitemheight = 30 ;
	_deltaseparation = 40 ;

	this->_currenttouches = StackViewTouches::ZeroTouches ;
	this->_currentmanipulationmode = StackViewManipulationMode::Enable ;
	this->_currentmanipulationstate = StackViewManipulationState::Idle;
	initarrrayfunctions();
}

void StackView::loaddatasource()
{ 
	this->_numberofitems = this->_datasource->ThumbsList->Size ;
	this->_maxsthumbsgridcale = _numberofitems  ;
	LoadItems();
	for (int i = 0; i < _numberofitems ; i++)
		((StackViewItem^)this->_thumbsgrid->Children->GetAt(i))->MediumSource = this->_datasource->MediumList->GetAt(i);
}

void StackView::LoadItems()
{
	for (int i = 0; i < _numberofitems ; i++)
	{ 
		///Creamos y añadimos un item al stack
		StackViewItem^ _tmpitem = ref new StackViewItem();
		_tmpitem->ThumbSource = this->_datasource->ThumbsList->GetAt(i);
		_tmpitem->ItemNumber = i ;
		_tmpitem->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Left ;
		float64 _tmpangle =  rand()%20 - 10; //Angulo aleatorio del item
		_tmpitem->InitialAngle = _tmpangle ;
		_tmpitem->RotateAngle = _tmpangle ;
		_tmpitem->LockItem();
		///add handler 
		_tmpitem->OnStackViewItemManipulationStarted += ref new BookReader::StackViewItemManipulationStartedEventHandler(this, &BookReader::StackView::StackViewItemManipulationStarted_1);
		//llenado adicional
		_tmpitem->ItemHeight = this->_stackviewitemheight ;
		_tmpitem->ItemWidth = this->_stackviewitemwidth ;		
		_tmpitem->FullScreenHeight =  _fullscreenheight  ;		
		_tmpitem->FullScreenWidth =  _fullscreenwidth ;		
		_tmpitem->FullScreenPositionX =  _fullscreenX ;		
		_tmpitem->FullScreenPositionY = _fullscreenY ;		
		_tmpitem->TranslateX = this->_deltaseparation / 2 ;						
		_tmpitem->FinalPosition = this->_deltaseparation / 2 + (this->_stackviewitemwidth + this->_deltaseparation) * i ;
		this->_thumbsgrid->Children->Append(_tmpitem);		
	}
}

//Funcion auxiliar :  init grids -> thumb and full
void StackView::initstackview()
{
	this->_currentstate =  StackViewState::Close ;
	this->_stackmanipulationstate = StackManipulationState::Enable ;
	this->_numberofpointers  = 0 ;
	this->_currentthumbsgridscale = 1.0 ;
	this->_maxsthumbsgridcale =  1 ;

	this->_thumbsgrid		= ref new Windows::UI::Xaml::Controls::Grid();
	this->_thumbsgrid->PointerPressed += ref new PointerEventHandler(this, &BookReader::StackView::ThumbsGrid_PointerPressed_1);
	this->_thumbsgrid->PointerReleased += ref new PointerEventHandler(this, &BookReader::StackView::ThumbsGrid_PointerReleased_1);
	this->_thumbsgrid->Tapped += ref new TappedEventHandler(this, &BookReader::StackView::ThumbsGrid_Tapped_1 );
	this->_thumbsgrid->ManipulationCompleted += ref new ManipulationCompletedEventHandler(this, &BookReader::StackView::ThumbsGrid_ManipulationCompleted_1);
	this->_thumbsgrid->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, &BookReader::StackView::ThumbsGrid_ManipulationDelta_1);

	//init panelcontainer
	this->_firstitem =  ref new Grid();
	this->_lastitem =  ref new Grid();
	this->_panelcontainer = ref new StackPanel();
	this->_panelcontainer->Orientation = Orientation::Horizontal ;
	this->Children->Append(this->_panelcontainer);

	///Add the _thumbsgrid to panelcontainer
	this->_panelcontainer->Children->Append(this->_firstitem );
	this->_panelcontainer->Children->Append(this->_thumbsgrid );
	this->_panelcontainer->Children->Append(this->_lastitem );

	this->_thumbsgrid->HorizontalAlignment =  Windows::UI::Xaml::HorizontalAlignment::Center ;
	this->_thumbsgrid->ManipulationMode  = ManipulationModes::All ;
	this->_thumbsgrid->Background = ref new SolidColorBrush(Windows::UI::Colors::Transparent);

	this->_fullscreengrid	= ref new Windows::UI::Xaml::Controls::Grid();
	this->_fullscreengrid->Visibility =  Windows::UI::Xaml::Visibility::Collapsed; // maybe opacity 
	this->Children->Append(this->_fullscreengrid);

	initvariables();
	setGridThumbAnimation();
}

void StackView::initvariables()
{
	this->_datasource = nullptr ;

	this->_stackviewitemheight = 0;
	this->_stackviewitemwidth = 0;
	this->_deltaseparation = 0 ;
	_fullscreenheight = 0 ;
	_fullscreenwidth = 0 ; 
	_fullscreenX = 0 ;
	_fullscreenY = 0 ; 

	this->_numberofitems = 0 ;
}

void StackView::setGridThumbAnimation()
{
	_gridthumbsanimation =   ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	Windows::Foundation::TimeSpan ts;
	ts.Duration = 3000000 ;
	Windows::UI::Xaml::Duration dur(ts) ;
	_gridthumbsanimation->Duration =  dur ;
	_gridthumbsanimation->EnableDependentAnimation = true ;
	_gridthumbsstory = ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	_gridthumbsstory->Children->Append(_gridthumbsanimation);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(_gridthumbsstory , "(Grid.Width)");
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(_gridthumbsstory , _thumbsgrid);
}

void StackView::updatestackitems()
{
	for (int i = 0; i < this->_numberofitems; i++)
	{
		((StackViewItem^)this->_thumbsgrid->Children->GetAt(i))->TranslateX =  this->_deltaseparation / 2 +  i * ((_thumbsgrid->ActualWidth  - _stackviewitemwidth - _deltaseparation) / (_numberofitems	 - 1 )) ;
		((StackViewItem^)this->_thumbsgrid->Children->GetAt(i))->RotateAngle = (1.0 - this->_currentthumbsgridscale / this->_maxsthumbsgridcale) * ((StackViewItem^)this->_thumbsgrid->Children->GetAt(i))->InitialAngle  ;
	}
	
}

void StackView::openthumbstack()
{
	this->_gridthumbsanimation->To = this->_numberofitems * ( this->_stackviewitemwidth + this->_deltaseparation ) ;
	this->_gridthumbsstory->Begin();
	for (int i = 0; i < _numberofitems ; i++)
	{
		((StackViewItem^)this->_thumbsgrid->Children->GetAt(i))->Open();
	}
	this->_currentstate = StackViewState::Open;
	this->_currentthumbsgridscale = this->_maxsthumbsgridcale ;
}

void StackView::closethumbstack()
{
	this->_gridthumbsanimation->To = this->_stackviewitemwidth + this->_deltaseparation ;
	this->_gridthumbsstory->Begin();
	for (int i = 0; i < _numberofitems ; i++)
	{
		((StackViewItem^)this->_thumbsgrid->Children->GetAt(i))->Close();
	}
	this->_currentstate = StackViewState::Close;
	this->_currentthumbsgridscale = 1.0 ;
}

void BookReader::StackView::StackViewItemManipulationStarted_1(Platform::Object ^ sender , int32 _currentitem)
{

	this->_currentselecteditem = _currentitem ;
	
	 ///Bloqueo todos los items -> menos el manipulado
	if(this->_currentstate == StackViewState::Open)
	{
		this->_stackmanipulationtype = StackManipulationType::ItemManipulation ; 
		for (int i = 0; i < _numberofitems ; i++)
		{  
			if(i!= _currentitem)
				((StackViewItem^)this->_thumbsgrid->Children->GetAt(i))->LockItem();
		}	
	}

}

void BookReader::StackView::ThumbsGrid_Tapped_1(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
}

void BookReader::StackView::ThumbsGrid_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	//this->_numberofpointers-- ;
}

void BookReader::StackView::ThumbsGrid_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	if(_currentmanipulationstate == StackViewManipulationState::Idle)
		(this->*_pointerpressedfunctions[(int32)_currenttouches])();
}

void BookReader::StackView::ThumbsGrid_ManipulationStarted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ e)
{
	_currentmanipulationstate = StackViewManipulationState::Busy ;
}

void BookReader::StackView::ThumbsGrid_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{
	//Finaliza la manipulacion
	if ( e->IsInertial )
	{
		e->Complete();
		e->Handled =  true ;
		return ;
	} 

	if(_currenttouches == StackViewTouches::TwoTouches)
	{
		if(this->_stackmanipulationtype == StackManipulationType::StackManipulation)
		{
			this->_currentthumbsgridscale *= e->Delta.Scale ;
			if (this->_currentthumbsgridscale > this->_maxsthumbsgridcale)
				this->_currentthumbsgridscale = this->_maxsthumbsgridcale ;

			if ( this->_currentthumbsgridscale < 1.0)
				this->_currentthumbsgridscale =  1.0 ;

			this->_thumbsgrid->Width = this->_currentthumbsgridscale * ( this->_stackviewitemwidth + this->_deltaseparation )  ;
			//set all the properties
			updatestackitems();
		}

		if( this->_stackmanipulationtype == StackManipulationType::ItemManipulation)
		{
			//((StackViewItem^)this->_thumbsgrid->Children->GetAt(_currentselecteditem))->ItemTransform->CenterX = _stackviewitemwidth /2  ;
			//((StackViewItem^)this->_thumbsgrid->Children->GetAt(_currentselecteditem))->ItemTransform->CenterY = _stackviewitemheight /2  ;
			((StackViewItem^)this->_thumbsgrid->Children->GetAt(_currentselecteditem))->ItemTransform->TranslateX += e->Delta.Translation.X;
			((StackViewItem^)this->_thumbsgrid->Children->GetAt(_currentselecteditem))->ItemTransform->TranslateY += e->Delta.Translation.Y;
			((StackViewItem^)this->_thumbsgrid->Children->GetAt(_currentselecteditem))->ItemTransform->ScaleX *= e->Delta.Scale;
			((StackViewItem^)this->_thumbsgrid->Children->GetAt(_currentselecteditem))->ItemTransform->ScaleY *= e->Delta.Scale;
			((StackViewItem^)this->_thumbsgrid->Children->GetAt(_currentselecteditem))->ItemTransform->Rotation += e->Delta.Rotation;
		}
	}
}

void BookReader::StackView::ThumbsGrid_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e)
{

	if(_currenttouches == StackViewTouches::TwoTouches)
	{
		if(this->_stackmanipulationtype == StackManipulationType::StackManipulation)
		{
			if(this->_currentthumbsgridscale > 2.5 )
			{
				openthumbstack();
			}
			else
			{
				closethumbstack();
			}
		}

		if( this->_stackmanipulationtype == StackManipulationType::ItemManipulation)
		{
			((StackViewItem^)this->_thumbsgrid->Children->GetAt(_currentselecteditem))->AnimateItem();

		}
	}

	this->_numberofpointers = 0 ;
	this->_currentmanipulationmode = StackViewManipulationMode::Dislable;
	this->_currentmanipulationstate = StackViewManipulationState::Idle ;
	this->_currenttouches = StackViewTouches::ZeroTouches ;
}

#pragma region Pointer Functions

void StackView::initarrrayfunctions()
{
	///Funcione para settear el numero de toques
	this->_pointerpressedfunctions[0] = &StackView::zero_pointerpressed;
	this->_pointerpressedfunctions[1] = &StackView::one_pointerpresses;
	this->_pointerpressedfunctions[2] = &StackView::two_pointerpressed;
	this->_pointerpressedfunctions[3] = &StackView::N_pointerpressed;


}

bool StackView::zero_pointerpressed()
{
	this->_currenttouches = StackViewTouches::OneTouch;
	this->_stackmanipulationtype = StackManipulationType::StackManipulation;
	return true ;
}
	
bool StackView::one_pointerpresses()
{
	this->_currenttouches = StackViewTouches::TwoTouches; 
	return true ;
}
	
bool StackView::two_pointerpressed()
{
	if (this->_stackmanipulationtype == StackManipulationType::ItemManipulation)
		this->_currenttouches = StackViewTouches::TwoTouches;
	else
		this->_currenttouches = StackViewTouches::NTouches;

	return true ;
}
	
bool StackView::N_pointerpressed()
{
	return true ;
}

#pragma endregion
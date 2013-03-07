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

using namespace concurrency ;



StackViewItem::StackViewItem()
{ 
	this->InitItem();
	this->InitAnimationProperties();
	this->_number_of_pointers = 0 ; // Init el numero de items 
	this->_item_manipulation_state =  ItemManipulationState::ItemManipulationEnable ; //init state
	this->_item_state =  StackViewItemState::Close ;
	Canvas::SetZIndex(this, 1);
	this->_currentitemscale = 1.0 ;
	this->Background = ref new SolidColorBrush(Windows::UI::Colors::Red);
	 
	//Init image
	this->ImageItem =  ref new Windows::UI::Xaml::Controls::Image();
	this->Children->Append(this->ImageItem);
		
}		

void StackViewItem::InitItem()
{
	
	this->stackviewitem_transform =  ref new CompositeTransform();
	this->RenderTransform = this->stackviewitem_transform ;
	
	
	//todo timpo de manipulacion
	//this->ManipulationMode = ManipulationModes::All;

	this->PointerPressed += ref new PointerEventHandler(this, &BookReader::StackViewItem::Item_PointerPressed_1);
	this->PointerReleased += ref new PointerEventHandler(this, &BookReader::StackViewItem::Item_PointerReleased_1);
	//this->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, &BookReader::StackViewItem::Item_ManipulationDelta_1);
	//this->ManipulationCompleted += ref new ManipulationCompletedEventHandler(this, &BookReader::StackViewItem::Item_ManipulationCompleted_1);
	//this->ManipulationInertiaStarting += ref new ManipulationInertiaStartingEventHandler(this, &BookReader::StackViewItem::Item_ManipulationInertiaStarting_1);

}

void StackViewItem::ResetItem()
{
	this->_number_of_pointers = 0 ;
}

void StackViewItem::AnimateItem()
{
	if(this->stackviewitem_transform->ScaleX > 2)
	{
		AnimateToFullScreen();
		this->translateY_animation->To =_full_screen_positionY ;
		this->translateY_story->Begin();
	}
	else
	{
		AnimateToThumb();
		this->translateY_animation->To =0.0;
		this->translateY_story->Begin();
		//Canvas::SetZIndex(this, 1);//hacerlo cuando termine la animacion
	}
	this->_number_of_pointers = 0 ;
	
}

void StackViewItem::InitAnimationProperties()
{
	this->translateX_animation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation(); ;
	Windows::Foundation::TimeSpan ts;
	ts.Duration = 3000000 ;
	Windows::UI::Xaml::Duration dur(ts) ;
	translateX_animation->Duration = dur  ;
	this->animation_story =  ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	this->animation_story->Children->Append(translateX_animation) ;
		
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(this->translateX_animation, this->stackviewitem_transform) ;
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(this->translateX_animation , "TranslateX") ;
	 
	this->rotate_animation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation(); ;	
	this->rotate_animation->Duration = dur ;
	this->animation_story->Children->Append(rotate_animation) ;	
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(this->rotate_animation, this->stackviewitem_transform) ;
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(this->rotate_animation , "Rotation") ;

	translateY_story = ref new Windows::UI::Xaml::Media::Animation::Storyboard();
	this->translateY_animation = ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation(); ;	
	this->translateY_animation->Duration = dur ;
	this->translateY_story->Children->Append(translateY_animation) ;	
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(this->translateY_animation, this->stackviewitem_transform) ;
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(this->translateY_animation , "TranslateY") ;
 

	/// Animation to Fullscreen
	this->scale_story = ref new Windows::UI::Xaml::Media::Animation::Storyboard();

	this->scaleX_animation =  ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->scaleX_animation->Duration = dur ;
	this->scale_story->Children->Append(scaleX_animation);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(this->scaleX_animation, this->stackviewitem_transform) ;
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(this->scaleX_animation , "ScaleX") ;

	this->scaleY_animation =  ref new Windows::UI::Xaml::Media::Animation::DoubleAnimation();
	this->scaleY_animation->Duration = dur ;
	this->scale_story->Children->Append(scaleY_animation);
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTarget(this->scaleY_animation, this->stackviewitem_transform) ;
	Windows::UI::Xaml::Media::Animation::Storyboard::SetTargetProperty(this->scaleY_animation , "ScaleY") ;

	this->scale_story->Completed += ref new EventHandler<Platform::Object^>(this, &BookReader::StackViewItem::ScaleStoryboard_Completed_1);
}

void StackViewItem::LoadImages(Platform::String ^ uri)
{ 
	this->ImageItem = ref new Image();
	 create_task( Windows::Storage::StorageFile::GetFileFromApplicationUriAsync(ref new Windows::Foundation::Uri("ms-appx:///"+ thumb_source) )).then([this]( Windows::Storage::StorageFile ^ file)
			{
				if(file)
				{
					 create_task(file->OpenAsync(Windows::Storage::FileAccessMode::Read)).then([this]( Windows::Storage::Streams::IRandomAccessStream^ fileStream)
					{
					   // Set the image source to the selected bitmap
					   auto bitmapImage = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage();
					   //bitmapImage->DecodePixelHeight = 140 ;
					   //bitmapImage->DecodePixelWidth = 140 ;			   
					   bitmapImage->SetSource(fileStream);
					   this->ImageItem->Source = bitmapImage;						   
					});
				}
			});  

	 
}

void StackViewItem::AnimateTo(float64 _x , float64 _angle)
{
	this->translateX_animation->To = _x ;
	if (_angle>0)
		this->rotate_animation->To = _initial_angle ; 
	else
		this->rotate_animation->To = 0.0 ; 
	this->animation_story->Begin() ;
	this->_number_of_pointers = 0 ;

	
}
 

void StackViewItem::LockItem()
{
	this->_item_manipulation_state =  ItemManipulationState::ItemManipulationDislable ;
}


void StackViewItem::UnLockItem()
{
	this->_item_manipulation_state =  ItemManipulationState::ItemManipulationEnable;
}

//animate the item to its final position
void StackViewItem::Open()
{
	this->_item_state =  StackViewItemState::Open ;
	this->translateX_animation->To = _final_position ;
	this->rotate_animation->To = 0.0; 
	this->animation_story->Begin() ;
	this->_number_of_pointers = 0 ;
}
		
//animate the item to its initial position
void StackViewItem::Close()
{
	this->_item_state =  StackViewItemState::Close ;
	this->translateX_animation->To = _initial_position ;
	this->rotate_animation->To = _initial_angle; 
	this->animation_story->Begin() ;
	this->_number_of_pointers = 0 ;
}
 
//Se inicia cuando termina la manipulacion <=> scale > 2
void StackViewItem::AnimateToFullScreen()
{
	 
	this->translateX_animation->To = _full_screen_positionX ;
	this->rotate_animation->To = 0.0 ; 
	this->animation_story->Begin() ;
	this->_number_of_pointers = 0 ;

	///inicializamos la animacion de scale
	this->scaleX_animation->To = this->_full_screen_width / this->ItemWidth ;
	this->scaleY_animation->To =  this->_full_screen_height / this->ItemHeight ;
	this->scale_story->Begin();
}

//se inicia cuando termina la manpulacion <=> scale <=  2
void StackViewItem::AnimateToThumb()
{
	 
	this->translateX_animation->To = _final_position ;
	this->translateY_animation->To = 0.0 ;
	this->rotate_animation->To = 0.0 ; 
	this->animation_story->Begin() ;
	this->_number_of_pointers = 0 ;

	//animacion de scale
	this->scaleX_animation->To = 1.0 ;
	this->scaleY_animation->To =  1.0 ;
	this->scale_story->Begin();
}


void BookReader::StackViewItem::Item_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	this->_number_of_pointers +=  1 ;
	if(this->_number_of_pointers == 2)
	{
		Canvas::SetZIndex(this , 100);
		this->OnStackViewItemManipulationStarted(this->ImageItem , this->_item_number);
	}		
}
		
void BookReader::StackViewItem::Item_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	//this->_number_of_pointers -= 1 ; 
	if(this->_number_of_pointers < 1)
	{
		Canvas::SetZIndex(this, 50);
	}
}

void BookReader::StackViewItem::Item_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e)
{
	if(e->IsInertial)
	{
		e->Complete();
	}

	if(this->_number_of_pointers == 2 && this->_item_manipulation_state == ItemManipulationState::ItemManipulationEnable ) // Habilitado para manipulacion
	{
		this->stackviewitem_transform->TranslateX	+= e->Delta.Translation.X ;
		this->stackviewitem_transform->TranslateY	+= e->Delta.Translation.Y ;
		this->stackviewitem_transform->Rotation		+= e->Delta.Rotation ;
		this->_currentitemscale *= e->Delta.Scale ;
		this->stackviewitem_transform->ScaleX		*= this->_currentitemscale ;
		this->stackviewitem_transform->ScaleY		*= this->_currentitemscale ;
	}

	if(this->_currentitemscale > 2.0)
	{
		//Change source to item cuando esta creciendo 
	} 
}

void BookReader::StackViewItem::Item_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e)
{
	if(this->stackviewitem_transform->ScaleX < 2 ) //Restaurar item
	{
		this->AnimateToThumb();
	}
	else
	{
		this->AnimateToFullScreen();
	}

	this->_number_of_pointers = 0 ;
}

void BookReader::StackViewItem::Item_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs ^ e)
{
	
}

void BookReader::StackViewItem::Item_Tapped_1(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	
}


void BookReader::StackViewItem::ScaleStoryboard_Completed_1(Platform::Object^ sender, Platform::Object^ e)
{
	if(this->stackviewitem_transform->ScaleX < 1.2)
		Canvas::SetZIndex(this, 1);
}


 

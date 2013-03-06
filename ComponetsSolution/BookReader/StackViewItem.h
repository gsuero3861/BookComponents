#include "pch.h"

namespace BookReader
{
	//Controla si el item es manipulable o no -> lock <-> unlock
	public enum class ItemManipulationState
	{
		ItemManipulationEnable,
		ItemManipulationDislable
	};

	//Controla si el tiem esta abierto o cerrado
	public enum  class StackViewItemState
	{
		Open,
		Close
	};

	ref class StackViewItem ;

/**	public delegate void ManipulateItemEnableEventHandler(Platform::Object ^ sender , int32 _currentitem);
	public delegate void ManipulateItemDislableEventHandler(Platform::Object ^ sender , int32 _currentitem);
	public delegate void ManipulationItemDeltaEventHandler(Platform::Object ^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ args);
	public delegate void ManipulationItemCompletedEventHandler(Platform::Object ^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ args);
	public delegate void TappedItemStackEventHandler(Platform::Object^ sender , Windows::UI::Xaml::Input::TappedRoutedEventArgs^ args);	
	*/
	///ocurre cuando se inicia la manipulacion del item -> bloquea  todo lo demas
	public delegate void StackViewItemManipulationStartedEventHandler(Platform::Object ^ sender , int32 _currentitem);

	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class StackViewItem sealed : public Windows::UI::Xaml::Controls::Grid 
	{
	public:
		StackViewItem(); 
		void AnimateTo(float64 _x , float64 _angle) ;
		void LockItem();
		void UnLockItem();
		void ResetItem();
		void AnimateItem();
		void Open();
		void Close();	

		event StackViewItemManipulationStartedEventHandler ^ OnStackViewItemManipulationStarted ; 

		property Platform::String^ ThumbSource
		{
			void set(Platform::String^ value)
			{
				this->thumb_source =  value ;
				//this->ImageItem =  ref new Windows::UI::Xaml::Controls::Image();
				//this->LoadImages("ms-appx:///"+ thumb_source);
				//this->Children->Append(this->ImageItem);				 
				//this->Background = ref new Windows::UI::Xaml::Media::SolidColorBrush(Windows::UI::Colors::Bisque) ;
				//this->LoadImages(this->thumb_source);
				//this->ImageItem->Source =  ref new Windows::UI::Xaml::Media::Imaging::BitmapImage(ref new Windows::Foundation::Uri(thumb_source));					
				LoadImages(value);
			}

			Platform::String^  get(){ return "";}
		}

		property Platform::String^ MediumSource
		{
			void set(Platform::String^ value){ this->medium_source =  value ; }
			Platform::String^  get(){ return "";}
		}

		 

		property int32 ItemNumber
		{
			int32 get()
			{
				return _item_number ;
			}

			void set(int32 value)
			{
				_item_number =  value ;
			}
		}
			
		property float64 ItemWidth
		{
			float64 get()
			{
				return this->Width;
			}

			void set(float64 value)
			{
				this->Width = value ;
				this->stackviewitem_transform->CenterX = this->Width / 2 ;

			}
		}

		property float64 ItemHeight
		{
			float64 get()
			{
				return this->Height;
			}

			void set(float64 value)
			{
				this->Height = value ;
				this->stackviewitem_transform->CenterY = this->Height / 2 ;
			}
		}

		property float64 RotateAngle
		{
			float64 get()
			{
				return this->_rotatetransform_angle ;
			}

			void set(float64 value)
			{
				this->_rotatetransform_angle = value ;
				this->stackviewitem_transform->Rotation = this->_rotatetransform_angle ;
			}
		}

		property float64 TranslateX
		{
			float64 get(){ return this->_translatetransform_X ;		}
			void set(float64 value)	
			{	
				this->_translatetransform_X = value ;
				this->stackviewitem_transform->TranslateX = _translatetransform_X ;
			}
		}

		property float64 InitialAngle
		{
			float64 get()
			{
				return _initial_angle ;
			}

			void set(float64 value)
			{
				this->_initial_angle =  value ;
				this->stackviewitem_transform->Rotation = this->_initial_angle ;
			}
		}

		property float64 FinalPosition
		{
			float64 get(){ return _final_position ; }
			void set(float64 value) { this->_final_position =  value ; }
		}

		property float64 InitialPosition
		{
			float64 get(){ return _initial_position ; }
			void set(float64 value) { this->_initial_position =  value ; }
		}

		property float64 FullScreenPositionX
		{
			void set(float64 value) { this->_full_screen_positionX =  value ; }
			float64 get(){ return this->_full_screen_positionX ;}
		}

		property float64 FullScreenPositionY
		{
			void set(float64 value) { this->_full_screen_positionY =  value ; }
			float64 get(){ return this->_full_screen_positionY ;}
		}

		property float64 FullScreenHeight
		{
			void set(float64 value) { this->_full_screen_height =  value ; }
			float64 get(){ return this->_full_screen_height ;}
		}

		property float64 FullScreenWidth
		{
			void set(float64 value) { this->_full_screen_width =  value ; }
			float64 get(){ return this->_full_screen_width ;}
		}
 

		property Windows::UI::Xaml::Media::CompositeTransform ^ ItemTransform
		{
			void set(Windows::UI::Xaml::Media::CompositeTransform ^ value){ stackviewitem_transform =  value ;}
			Windows::UI::Xaml::Media::CompositeTransform ^ get()
			{
				return this->stackviewitem_transform ;
			}
		}

	private:

		//Contenido
		Windows::UI::Xaml::Controls::Image ^ ImageItem ;
		Platform::String ^ thumb_source ;
		Platform::String ^ medium_source ;

		///Variables de valor
		int32 _item_number ;
		float64 _rotatetransform_angle ;
		float64 _translatetransform_X ;
		float64 _initial_angle ;
		float64 _final_position, _initial_position ;
		float64 _full_screen_positionX ;
		float64 _full_screen_positionY ;
		float64 _full_screen_height  ;
		float64 _full_screen_width ;

		//Variables auxliares
		int16 _number_of_pointers ;
		ItemManipulationState _item_manipulation_state; //Verifica si se puede hacer manipulaciones sobre el item	
		StackViewItemState _item_state ; //Control de estado del item 
		float64 _currentitemscale ;
		
		//funciones auxiliares
		void InitItem(); 
		void InitAnimationProperties() ;
		void AnimateToFullScreen();
		void AnimateToThumb();

		//Funciones auxliares de carga de datos
		void LoadImages(Platform::String ^ uri);

		void Item_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void Item_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void Item_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e);
		void Item_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e);
		void Item_ManipulationInertiaStarting_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs ^ e);
		void Item_Tapped_1(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
		
		Windows::UI::Xaml::Media::CompositeTransform ^ stackviewitem_transform; //Render transform 
		Windows::UI::Xaml::Media::Animation::Storyboard ^ animation_story ;
		Windows::UI::Xaml::Media::Animation::DoubleAnimation ^ translateX_animation;
		Windows::UI::Xaml::Media::Animation::DoubleAnimation ^ translateY_animation;
		Windows::UI::Xaml::Media::Animation::DoubleAnimation ^ rotate_animation;

		Windows::UI::Xaml::Media::Animation::Storyboard ^ translateY_story ;

		Windows::UI::Xaml::Media::Animation::Storyboard ^ scale_story ;
		Windows::UI::Xaml::Media::Animation::DoubleAnimation ^ scaleX_animation ;
		Windows::UI::Xaml::Media::Animation::DoubleAnimation ^ scaleY_animation ;


	};
}
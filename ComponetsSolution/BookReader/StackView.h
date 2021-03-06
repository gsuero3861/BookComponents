#include "pch.h"
#include <collection.h>

namespace BookReader
{
	public enum class StackViewState
	{
		Open,
		Close
	};

	public enum class StackManipulationState
	{
		Enable,
		Dislable,
		ItemManipulation //A item is being manipulating
	};


	public enum class StackViewTouches
	{
		ZeroTouches,
		OneTouch,
		TwoTouches,
		NTouches
	};

	public enum class StackViewManipulationState
	{
		Idle,
		Busy
	};
	public enum class StackViewManipulationMode
	{
		Enable,
		Dislable,
		ItemManipulation
	};

	public enum class StackManipulationType
	{
		StackManipulation,
		ItemManipulation
	};


	public delegate void StackManipulationStartedEventHandler(Platform::Object ^ sender , int32 args);
	public delegate void StackManipulationFinishedEventHandler(Platform::Object ^ sender , int32 stacknumber, int32 citem);
	public delegate void StackAnimationCompletedEventHandler(Platform::Object ^ sender , int32 stacknumber);



	public ref class StackView sealed : public Windows::UI::Xaml::Controls::Grid
	{
#pragma region Constructor and Events
	public  :

		StackView();	

		event StackManipulationStartedEventHandler ^ StackManipulationStarted ;
		event StackManipulationFinishedEventHandler ^ StackManipulationFinished ; 
		event StackAnimationCompletedEventHandler ^ StackAnimationCompleted ;

#pragma endregion

#pragma region Properties


	public:

		property Platform::Object^ DataSource
		{
			void set(Platform::Object^ value)
			{
				this->_datasource = (BookData::StackDataSource^)value ;
				loaddatasource();
			}
			Platform::Object^ get(){return this->_datasource ;}
		}

		/** Older data input implementation
		property Windows::Foundation::Collections::IVector<Platform::String^> ^ ThumbItemsList
		{		
			void set( Windows::Foundation::Collections::IVector<Platform::String^> ^ value  )
			{ 
				this->_thumbitemlist = value ; 
				this->_numberofitems = this->_thumbitemlist->Size ;
				this->_maxsthumbsgridcale = _numberofitems  ;
				LoadItems();
			}
			Windows::Foundation::Collections::IVector<Platform::String^>^ get(){ return nullptr ; }
		}
		*/
		property Windows::Foundation::Collections::IVector<Platform::String^> ^ MediumItemsList
		{		
			void set( Windows::Foundation::Collections::IVector<Platform::String^> ^ value  )
			{
				this->_mediumitemlist = value ; 				 
				/**for (int i = 0; i < _numberofitems ; i++)
				{  
					((StackViewItem^)this->_thumbsgrid->Children->GetAt(i))->MediumSource = this->_mediumitemlist->GetAt(i);
				}*/
			}
			Windows::Foundation::Collections::IVector<Platform::String^>^ get(){ return this->_mediumitemlist ; }
		}

		property Windows::Foundation::Collections::IVector<Platform::String^> ^ FullScreenItemsList
		{							
			void set( Windows::Foundation::Collections::IVector<Platform::String^> ^ value  ){ this->_fullscreenitemlist = value ; }
			Windows::Foundation::Collections::IVector<Platform::String^>^ get(){ return this->_fullscreenitemlist ; }
		}
		
		//height  of each item
		property float64 StackViewItemHeight
		{
			void set(float64 value)
			{ 
				this->_stackviewitemheight = value ; 
				_thumbsgrid->Height = value ;
				if(this->_datasource != nullptr)
				{
					for (int i = 0; i < _numberofitems ; i++)
					{  
						((StackViewItem^)this->_thumbsgrid->Children->GetAt(i))->ItemHeight = this->_stackviewitemheight ;
					}
				}
			}
			float64 get(){ return this->_stackviewitemheight ; };
		}
		 
		//width of each item
		property float64 StackViewItemWidth
		{
			float64 get(){ return this->_stackviewitemwidth ; }
			void set(float64 value)
			{ 
				this->_stackviewitemwidth =  value ; 
			
				if(this->_datasource != nullptr)
				{
					for (int i = 0; i < _numberofitems ; i++)
					{  
						((StackViewItem^)this->_thumbsgrid->Children->GetAt(i))->ItemWidth = this->_stackviewitemwidth ;
					}
				}
			}
		}

		//Separation between each item 
		property float64 DeltaItemSeparation
		{
			float64 get(){ return this->_deltaseparation ; }
			void set(float64 value)
			{
				this->_deltaseparation = value ;
				//Tranformadas iniciales
				if(this->_datasource != nullptr)
				{
					for (int i = 0; i < _numberofitems ; i++)
					{  
						((StackViewItem^)this->_thumbsgrid->Children->GetAt(i))->TranslateX = this->_deltaseparation / 2 ;					
						((StackViewItem^)this->_thumbsgrid->Children->GetAt(i))->FinalPosition = this->_deltaseparation / 2 + (this->_stackviewitemwidth + this->_deltaseparation) * i ; 
					}
				}
			}
		}

		//size of an item when it's fullscreen
		property float64 FullSreenItemHeight
		{
			float64 get(){ return this->_fullscreenheight ; }
			void set(float64 value)
			{
				this->_fullscreenheight =  value ; 
				if(this->_datasource != nullptr)
				{
					for (int i = 0; i < _numberofitems ; i++)
					{  
						((StackViewItem^)this->_thumbsgrid->Children->GetAt(i))->FullScreenHeight =  value ;
					}
				}
			}
		}

		//size of an item when it's fullscreen
		property float64 FullSreenItemWidth
		{
			float64 get(){ return this->_fullscreenwidth ; }
			void set(float64 value)
			{ 
				this->_fullscreenwidth =  value ; 
				if(this->_datasource != nullptr)
				{
					for (int i = 0; i < _numberofitems ; i++)
					{  
						((StackViewItem^)this->_thumbsgrid->Children->GetAt(i))->FullScreenWidth =  value ;
					}
				}
			}
		}

		//size of all the stack ->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		property float64 StackViewHeight
		{
			void set(float64 value) 
			{ 
				//this->Height = value ; 
				this->_firstitem->Height = value;
				this->_lastitem->Height = value ;
			}
			float64 get(){return 0 ;}
		}

		//size of all the stack 
		property float64 StackViewWidth
		{
			void set(float64 value) 
			{
				this->_firstitem->Height = value;
				this->_lastitem->Height = value ;
			}
			float64 get(){return 0 ;}
		}

		property float64 StackViewMargin
		{
			void set(float64 value) 
			{
				this->_firstitem->Height = value;
				this->_lastitem->Height = value ;
				this->_firstitem->Width = value;
				this->_lastitem->Width = value ;
			}
			float64 get(){return 0 ;}
		}


		//position when an iten is full screen
		property float64 FullScreenX 
		{
			float64 get(){ return this->_fullscreenX ; }
			void set(float64 value)
			{
				this->_fullscreenX =  value  ; 
				if(this->_datasource != nullptr) 
					for (int i = 0; i < _numberofitems ; i++) 
						((StackViewItem^)this->_thumbsgrid->Children->GetAt(i))->FullScreenPositionX =  value ; 
			}
		}

		//position when an iten is full screen
		property float64  FullScreenY
		{
			float64 get(){ return this->_fullscreenY ;}
			void set(float64 value)
			{
				this->_fullscreenY =  value ; 
				if(this->_datasource != nullptr) 
					for (int i = 0; i < _numberofitems ; i++) 
						((StackViewItem^)this->_thumbsgrid->Children->GetAt(i))->FullScreenPositionY = value ; 
			}
		}

		//to send when ocurr teh manipulation event
		property int32  StackNumber
		{
			int32 get(){ return this->_stacknumber ;}
			void set(int32 value)
			{ 
				this->_stacknumber  =  value ;
			}
		}

	private :
				
		///references to the sets of paths to the diferrents resolutions of images => CHANGED FOR THE DATASOURCE
		/**Windows::Foundation::Collections::IVector<Platform::String^> ^ _thumbitemlist ;*/
		Windows::Foundation::Collections::IVector<Platform::String^> ^ _mediumitemlist ;
		Windows::Foundation::Collections::IVector<Platform::String^> ^ _fullscreenitemlist ; 
	
		///variables auxliares -> properties
		float64 _stackviewitemheight,  _stackviewitemwidth ;
		float64 _deltaseparation ; //separation between each item
		float64 _fullscreenheight, _fullscreenwidth ; //max width and height del item full screen
		float64 _fullscreenX , _fullscreenY ; //horizontal and vertical position when an item is full screen
		int32 _stacknumber ;

#pragma endregion

#pragma region Public Methods
	public:
		void LoadItems();

		typedef bool (StackView:: * FunctionPointerPressed)();
		bool zero_pointerpressed();
		bool one_pointerpresses();
		bool two_pointerpressed();
		bool N_pointerpressed();


#pragma endregion

#pragma region Array Functions Pointers
		
	private:
		void initarrrayfunctions();
		FunctionPointerPressed _pointerpressedfunctions[4];

#pragma endregion



#pragma region Controls and Auxiliar Variables

	private:

		BookData::StackDataSource^ _datasource ;

		///Varibles Auxiliares -> uso
		int32 _numberofitems ; //numero de items del stack
		int16 _numberofpointers ; //numero de toques actualmente
		int16 _currentselecteditem; //actual item en caso de ser manipulado
		float64 _currentthumbsgridscale ;
		float64 _maxsthumbsgridcale ;
		
		StackManipulationState _stackmanipulationstate ;

		StackViewState _currentstate ;
		StackViewTouches _currenttouches ;
		StackViewManipulationMode _currentmanipulationmode ;
		StackViewManipulationState _currentmanipulationstate;
		StackManipulationType _stackmanipulationtype ;
		//Stack Adicional para controlar el ancho del stack
		Windows::UI::Xaml::Controls::StackPanel^ _panelcontainer ;
		Windows::UI::Xaml::Controls::Grid ^ _firstitem ;
		Windows::UI::Xaml::Controls::Grid ^ _lastitem ;
		///Controles principales  => 1 : los thumbs 2: fullscreen
		Windows::UI::Xaml::Controls::Grid ^ _thumbsgrid ;
		Windows::UI::Xaml::Controls::Grid ^ _fullscreengrid ;	

		//Animation of thumbsgrid
		Windows::UI::Xaml::Media::Animation::DoubleAnimation^ _gridthumbsanimation ;
		Windows::UI::Xaml::Media::Animation::Storyboard^ _gridthumbsstory;

#pragma endregion

#pragma region Private Methods
		///Funciones auxiliares
	private:
		void initstackview();//init the 2 grids thumbs  and fullscreen 
		void initvariables();
		void updatestackitems();
		void openthumbstack();
		void closethumbstack();

		void loaddatasource();

		void setGridThumbAnimation();
		
		void StackViewItemManipulationStarted_1(Platform::Object ^ sender , int32 _currentitem);
		void StackViewItemAnimationCompleted_1(Platform::Object ^ sender , int32 _currentitem);
		
		void ThumbsGrid_Tapped_1(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
		void ThumbsGrid_ManipulationStarted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ e);
		void ThumbsGrid_ManipulationCompleted_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e);
		void ThumbsGrid_ManipulationDelta_1(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e);
		void ThumbsGrid_PointerReleased_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void ThumbsGrid_PointerPressed_1(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);



#pragma endregion
  

	};
}
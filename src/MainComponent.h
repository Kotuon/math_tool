#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_graphics/juce_graphics.h>
#include <vector>
#include <memory>
#include "trace.hpp"

class MainComponent;
class Panel;
struct ControlPointLabel;

const std::vector< juce::uint32 > Color_List = {
    0xff1f77b4, 0xffff7f0e, 0xff2ca02c, 0xffd62728, 0xff9467bd,
    0xff8c564b, 0xffe377c2, 0xff7f7f7f, 0xffbcbd22, 0xff17becf };

struct ControlPoint {
    ControlPoint( double value_ ) : position(), value( value_ ), outer_radius( 10.0 ),
                                    inner_radius( outer_radius / 4.0 ),
                                    time_to_animate_when_selected( 0.05 ),
                                    time_since_selected( 0.0 ), selected( false ) {}

    ControlPoint( const ControlPoint& ) = delete;
    ControlPoint& operator=( const ControlPoint& ) = delete;

    juce::Point< float > GetPositionF() {
        return { static_cast< float >( position.x ), static_cast< float >( position.y ) };
    }

    float GetValueF() {
        return static_cast< float >( value );
    }

    float GetOuterRadiusF() {
        return static_cast< float >( outer_radius );
    }

    float GetInnerRadiusF() {
        return static_cast< float >( inner_radius );
    }

    void UpdatedIfSelected() {
    }

    void paint( juce::Graphics& g, juce::Point< float > position_ ) {
        position = { static_cast< float >( position_.x ), static_cast< float >( position_.y ) };
        g.fillEllipse( position_.x - GetInnerRadiusF(), position_.y - GetInnerRadiusF(), GetInnerRadiusF() * 2.f, GetInnerRadiusF() * 2.f );
        g.drawEllipse( position_.x - GetOuterRadiusF(), position_.y - GetOuterRadiusF(), GetOuterRadiusF() * 2.f, GetOuterRadiusF() * 2.f, 2.f );
    }

    juce::Point< double > position;
    double value;

    double outer_radius;
    double inner_radius;

    double time_to_animate_when_selected;
    double time_since_selected;

    bool hovered;
    bool selected;
};

class PointEditor : public juce::TextEditor {
public:
    void TextCallback();
    void ReturnCallback();
    void EscapeCallback();

public:
    ControlPointLabel* parent;
};

struct ControlPointLabel {
    ControlPointLabel( unsigned num );
    void MakeVisible( MainComponent* mc_, Panel* panel );

    void UpdateBounds( int x, int y, int i, float w );
    void UpdateValue( double value );

    juce::Label label;
    PointEditor editor;
    juce::TextButton remove_point;

    MainComponent* mc;

    unsigned id;
};

class Panel : public juce::Button::Listener {
public:
    Panel();

    void AddLabel();

    void Start( MainComponent* mc_, std::vector< std::shared_ptr< ControlPoint > >* cp, int window_height, int padding );

    void draw( juce::Graphics& g );

    juce::TextButton& GetHideButton();
    juce::TextButton& GetAddButton();
    juce::TextButton& GetExportButton();

    void buttonClicked( juce::Button* ) override;

private:
    MainComponent* mc;

    juce::Path main_panel;
    juce::TextButton hide_button;
    juce::TextButton add_point_button;
    juce::TextButton export_points;
    juce::Point< float > position;

    std::vector< std::unique_ptr< ControlPointLabel > > cp_labels;
    std::vector< std::shared_ptr< ControlPoint > >* control_points;

    float width;

    bool hidden;
};

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::AnimatedAppComponent {
public:
    //==============================================================================
    MainComponent();
    void precompute_bb_values();

    //==============================================================================
    void update();
    void paint( juce::Graphics& ) override;
    void resized() override;
    //==============================================================================
    void mouseDown( const juce::MouseEvent& event ) override;
    void mouseUp( const juce::MouseEvent& event ) override;
    void mouseDrag( const juce::MouseEvent& event ) override;

    unsigned GetMaxControlPoints() const;
    ControlPoint& GetControlPoint( unsigned index );

private:
    //==============================================================================
    // Your private member variables go here...

    std::vector< std::vector< double > > bb_values;

    std::vector< std::shared_ptr< ControlPoint > > control_points;
    std::shared_ptr< ControlPoint > selected_control_point = nullptr;

    Panel side_panel;

    unsigned max_control_points = 14;

    juce::Point< float > bottom_corner;
    juce::Point< float > top_corner;

    double top_value_limit;
    double bottom_value_limit;

    float top_screen_limit;
    float bottom_screen_limit;

    float fwindow_width;
    float fwindow_height;

    int window_width = 1600;
    int window_height = 800;

    int padding = 10;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( MainComponent )
};
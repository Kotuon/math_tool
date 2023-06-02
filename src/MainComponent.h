#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_graphics/juce_graphics.h>

class Panel : public juce::Button::Listener {
public:
    Panel() : main_panel(), hide_button(), width( 200.f ), position( -270.f, 10.f ) {
        hide_button.setButtonText( "Hide" );
        hide_button.setColour( juce::TextButton::buttonColourId, juce::Colours::white );
        hide_button.setColour( juce::TextButton::textColourOnId, juce::Colours::darkgrey );
        hide_button.setColour( juce::TextButton::textColourOffId, juce::Colours::darkgrey );
        hide_button.setBounds( static_cast< int >( position.x + width + 5 ),
                               static_cast< int >( position.y ), 60, 40 );
    }

    void draw( juce::Graphics &g, int window_height, int padding ) {
        main_panel.addRoundedRectangle( position.x, position.y, width,
                                        static_cast< float >( window_height - ( padding * 2 ) ), 5.f );
        g.fillPath( main_panel );
        g.strokePath( main_panel, juce::PathStrokeType( 1.f ) );
    }

    juce::TextButton &GetButton() {
        return hide_button;
    }

    void buttonClicked( juce::Button * ) override {
    }

private:
    juce::Path main_panel;
    juce::TextButton hide_button;

    float width;

    juce::Point< float > position;
};

struct ControlPoint {
    ControlPoint( juce::Point< double > position_ ) : position( position_ ), outer_radius( 10.0 ),
                                                      inner_radius( outer_radius / 4.0 ),
                                                      time_to_animate_when_selected( 0.05 ),
                                                      time_since_selected( 0.0 ), selected( false ) {}

    juce::Point< float > GetPositionF() {
        return { static_cast< float >( position.x ), static_cast< float >( position.y ) };
    }

    float GetOuterRadiusF() {
        return static_cast< float >( outer_radius );
    }

    float GetInnerRadiusF() {
        return static_cast< float >( inner_radius );
    }

    void UpdatedIfSelected() {
    }

    void paint( juce::Graphics &g ) {
        g.fillEllipse( GetPositionF().x - GetInnerRadiusF(), GetPositionF().y - GetInnerRadiusF(), GetInnerRadiusF() * 2.f, GetInnerRadiusF() * 2.f );
        g.drawEllipse( GetPositionF().x - GetOuterRadiusF(), GetPositionF().y - GetOuterRadiusF(), GetOuterRadiusF() * 2.f, GetOuterRadiusF() * 2.f, 1.f );
    }

    juce::Point< double > position;
    double outer_radius;
    double inner_radius;

    double time_to_animate_when_selected;
    double time_since_selected;

    bool hovered;
    bool selected;
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

    //==============================================================================
    void update();
    void paint( juce::Graphics & ) override;
    void resized() override;
    //==============================================================================
    void mouseDown( const juce::MouseEvent &event ) override;
    void mouseUp( const juce::MouseEvent &event ) override;
    void mouseDrag( const juce::MouseEvent &event ) override;

private:
    //==============================================================================
    // Your private member variables go here...

    std::vector< ControlPoint > control_points;
    ControlPoint *selected_control_point = nullptr;

    Panel side_panel;

    unsigned max_control_points = 4;

    int window_width = 800;
    int window_height = 600;

    int padding = 10;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( MainComponent )
};

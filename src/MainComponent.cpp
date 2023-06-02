/**
 * @file MainComponent.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-05-29
 *
 *
 *
 */

#include "MainComponent.h"
#include <algorithm>
#include <chrono>

//==============================================================================
MainComponent::MainComponent() {
    setSize( window_width, window_height );
    setFramesPerSecond( 60 );

    addAndMakeVisible( side_panel.GetButton() );

    for ( unsigned i = 0; i < max_control_points; ++i ) {
        control_points.push_back( ControlPoint( { static_cast< double >( i * ( ( window_width - ( 2 * padding ) ) / 3 ) + padding ), static_cast< double >( padding ) } ) );
    }
}

//==============================================================================
void MainComponent::update() {
    if ( !selected_control_point ) return;

    selected_control_point->time_since_selected += ( 1.0 / 60.0 );

    double t = selected_control_point->time_since_selected / selected_control_point->time_to_animate_when_selected;

    double new_radius = ( 1.0 - t ) * ( selected_control_point->outer_radius / 4.0 ) + ( t )*selected_control_point->outer_radius;
    selected_control_point->inner_radius = std::clamp( new_radius, selected_control_point->outer_radius / 4.0, selected_control_point->outer_radius );
}

void MainComponent::paint( juce::Graphics &g ) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll( getLookAndFeel().findColour( juce::ResizableWindow::backgroundColourId ) );

    g.setColour( juce::Colours::white );
    // g.drawLine( 10.f, static_cast< float >( window_height / 2 ), static_cast< float >( window_width - 10 ), static_cast< float >( window_height / 2 ), 2.f );
    // g.drawLine( 10.f, 10.f, 10.f, static_cast< float >( window_height - 10 ), 2.f );

    if ( control_points.size() >= max_control_points ) {

        juce::Path bezier_curve_path;
        bezier_curve_path.startNewSubPath( control_points[0].GetPositionF() );

        float t = 0.f;

        while ( t < 1.f ) {
            juce::Point< double > new_point = std::pow( 1 - t, 3 ) * control_points[0].position +
                                              3 * std::pow( 1 - t, 2 ) * t * control_points[1].position +
                                              3 * ( 1 - t ) * std::pow( t, 2 ) * control_points[2].position +
                                              std::pow( t, 3 ) * control_points[3].position;

            bezier_curve_path.lineTo( { static_cast< float >( new_point.x ), static_cast< float >( new_point.y ) } );
            t += 0.001f;
        }

        g.strokePath( bezier_curve_path, juce::PathStrokeType( 3.f ) );
    }

    for ( ControlPoint &control_point : control_points ) {
        control_point.paint( g );
    }
    // side_panel.draw( g, window_height, padding );
}

void MainComponent::resized() {
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    window_width = getWidth();
    window_height = getHeight();
}

//==============================================================================
void MainComponent::mouseDown( const juce::MouseEvent &event ) {
    juce::Point< double > mouse_position{ static_cast< double >( event.position.x ), static_cast< double >( event.position.y ) };

    for ( ControlPoint &control_point : control_points ) {
        double distance = std::pow( control_point.position.x - mouse_position.x, 2 ) +
                          std::pow( mouse_position.y - control_point.position.y, 2 );

        if ( distance <= std::pow( control_point.outer_radius, 2 ) ) {
            control_point.selected = true;
            control_point.time_since_selected = 0.0;

            selected_control_point = &control_point;
            return;
        }
    }

    if ( control_points.size() >= max_control_points ) return;

    control_points.push_back( ControlPoint( mouse_position ) );
}

void MainComponent::mouseUp( const juce::MouseEvent & ) {
    if ( !selected_control_point ) return;

    selected_control_point->selected = false;
    selected_control_point->inner_radius = selected_control_point->outer_radius / 4.0;
    selected_control_point = nullptr;
}

void MainComponent::mouseDrag( const juce::MouseEvent &event ) {
    if ( !selected_control_point ) return;

    juce::Point< double > mouse_position{ static_cast< double >( event.position.x ), static_cast< double >( event.position.y ) };

    juce::Point< double > new_control_point_position{ selected_control_point->position.x,
                                                      std::clamp< double >( mouse_position.y, padding, static_cast< double >( window_height - padding ) ) };

    selected_control_point->position = new_control_point_position;
}
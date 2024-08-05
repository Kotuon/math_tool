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
#include "trace.hpp"
#include <fstream>

void PointEditor::TextCallback() {
    juce::String string = getText();
    double value = string.getDoubleValue();

    parent->mc->GetControlPoint( parent->id ).value = value;
}

void PointEditor::ReturnCallback() {
    unfocusAllComponents();
}

void PointEditor::EscapeCallback() {
    unfocusAllComponents();
}

//==============================================================================
ControlPointLabel::ControlPointLabel( unsigned num ) : id( num ) {
    label.setColour( juce::Label::textColourId, juce::Colours::grey );
    label.setFont( juce::Font( 18.0f, juce::Font::plain ) );
    label.setText( "P" + juce::String( id ) + ": ", juce::dontSendNotification );

    editor.parent = this;
    editor.setFont( juce::Font( 18.f, juce::Font::plain ) );
    editor.setColour( juce::TextEditor::backgroundColourId, juce::Colours::white );
    editor.setColour( juce::TextEditor::textColourId, juce::Colours::grey );

    editor.onTextChange = std::bind( &PointEditor::TextCallback, &editor );
    editor.onReturnKey = std::bind( &PointEditor::ReturnCallback, &editor );
    editor.onEscapeKey = std::bind( &PointEditor::EscapeCallback, &editor );

    remove_point.setColour( juce::TextButton::buttonColourId, juce::Colours::white );
    remove_point.setColour( juce::TextButton::textColourOnId, juce::Colour( 0xff999999 ) );
    remove_point.setColour( juce::TextButton::textColourOffId, juce::Colour( 0xff999999 ) );
    remove_point.setButtonText( "-" );
}

void ControlPointLabel::MakeVisible( MainComponent* mc_, Panel* panel ) {
    mc = mc_;

    mc->addAndMakeVisible( label );
    mc->addAndMakeVisible( editor );
    mc->addAndMakeVisible( remove_point );

    remove_point.addListener( panel );
}

void ControlPointLabel::UpdateBounds( int x, int y, int i, float w ) {
    label.setBounds( x + 5, y + 5 + ( 50 * i ), static_cast< int >( w * 0.2f ), 30 );
    editor.setBounds( x + static_cast< int >( w * 0.2f ), y + 6 + ( 50 * i ), static_cast< int >( w * 0.55f ), 30 );
    remove_point.setBounds( x + 5 + static_cast< int >( w * 0.75f ), y + 5 + ( 50 * i ), static_cast< int >( w * 0.15f ), 30 );
}

void ControlPointLabel::UpdateValue( double value ) {
    if ( !editor.hasKeyboardFocus( false ) ) {
        editor.setText( juce::String( value, 4 ), juce::dontSendNotification );
    }
}

//==============================================================================
Panel::Panel() : mc( nullptr ), main_panel(), hide_button(), position( -200.f, 10.f ), width( 200.f ), hidden( true ) {
    hide_button.setButtonText( "Show" );
    hide_button.setColour( juce::TextButton::buttonColourId, juce::Colours::white );
    hide_button.setColour( juce::TextButton::textColourOnId, juce::Colour( 0xff999999 ) );
    hide_button.setColour( juce::TextButton::textColourOffId, juce::Colour( 0xff999999 ) );
    hide_button.setBounds( static_cast< int >( position.x + width + 5 ),
                           static_cast< int >( position.y ), 60, 40 );

    hide_button.addListener( this );

    add_point_button.setButtonText( "Add Point" );
    add_point_button.setColour( juce::TextButton::buttonColourId, juce::Colours::white );
    add_point_button.setColour( juce::TextButton::textColourOnId, juce::Colour( 0xff999999 ) );
    add_point_button.setColour( juce::TextButton::textColourOffId, juce::Colour( 0xff999999 ) );

    add_point_button.addListener( this );

    export_points.setButtonText( "Export Points to CSV" );
    export_points.setColour( juce::TextButton::buttonColourId, juce::Colours::white );
    export_points.setColour( juce::TextButton::textColourOnId, juce::Colour( 0xff999999 ) );
    export_points.setColour( juce::TextButton::textColourOffId, juce::Colour( 0xff999999 ) );

    export_points.addListener( this );
}

void Panel::AddLabel() {
    unsigned size = static_cast< unsigned >( cp_labels.size() );

    cp_labels.push_back( std::make_unique< ControlPointLabel >( size ) );

    cp_labels.back()->MakeVisible( mc, this );
}

void Panel::Start( MainComponent* mc_, std::vector< std::shared_ptr< ControlPoint > >* cp, int window_height, int padding ) {
    mc = mc_;
    control_points = cp;

    main_panel.addRoundedRectangle( position.x, position.y, width,
                                    static_cast< float >( window_height - ( padding * 2 ) ), 5.f );
}

void Panel::draw( juce::Graphics& g ) {

    g.setColour( juce::Colours::whitesmoke );
    g.fillPath( main_panel );
    g.setColour( juce::Colour( 0xff999999 ) );
    g.strokePath( main_panel, juce::PathStrokeType( 2.f ) );

    for ( int i = 0; i < static_cast< int >( control_points->size() ); ++i ) {
        cp_labels[i]->UpdateValue( ( *control_points )[i]->value );
        cp_labels[i]->UpdateBounds( static_cast< int >( position.x ), static_cast< int >( position.y ), i, width );
    }

    add_point_button.setBounds( static_cast< int >( position.x + 5 ),
                                static_cast< int >( position.y + ( 50 * control_points->size() ) ), static_cast< int >( width - 10 ), 25 );

    export_points.setBounds( static_cast< int >( position.x + 5 ),
                             static_cast< int >( position.y + 730 ), static_cast< int >( width - 10 ), 45 );
}

juce::TextButton& Panel::GetHideButton() {
    return hide_button;
}

juce::TextButton& Panel::GetAddButton() {
    return add_point_button;
}

juce::TextButton& Panel::GetExportButton() {
    return export_points;
}

void Panel::buttonClicked( juce::Button* button ) {
    if ( button == &hide_button ) {
        if ( hidden ) {
            juce::Point< float > last_position = position;
            position = { 5, position.y };
            main_panel.applyTransform( juce::AffineTransform::translation( position.x - last_position.x, 0 ) );
            hidden = false;
            hide_button.setButtonText( "Hide" );
            hide_button.setBounds( static_cast< int >( position.x + width + 5 ),
                                   static_cast< int >( position.y ), 60, 40 );
        } else {
            juce::Point< float > last_position = position;
            position = { -200.f, position.y };
            main_panel.applyTransform( juce::AffineTransform::translation( position.x - last_position.x, 0 ) );
            hidden = true;
            hide_button.setButtonText( "Show" );
            hide_button.setBounds( static_cast< int >( position.x + width + 5 ),
                                   static_cast< int >( position.y ), 60, 40 );

            for ( int i = 0; i < static_cast< int >( control_points->size() ); ++i ) {
                cp_labels[i]->UpdateBounds( static_cast< int >( position.x ),
                                            static_cast< int >( position.y + 20 ),
                                            i, width );
            }
        }
    } else if ( button == &add_point_button ) {
        if ( control_points->size() >= mc->GetMaxControlPoints() )
            return;

        control_points->push_back( std::make_shared< ControlPoint >( 0.0 ) );
        AddLabel();

    } else if ( button == &export_points ) {
        std::ofstream export_output;
        export_output.open( "bezier_points.csv" );
        export_output << "Point Values\n";
        for ( int i = 0; i < control_points->size(); ++i ) {
            export_output << std::to_string( ( *control_points )[i]->value ) + "\n";
        }
        export_output.close();
    } else {
        if ( control_points->size() < 3 )
            return;

        for ( int i = 0; i < cp_labels.size(); ++i ) {
            if ( button == &( cp_labels[i]->remove_point ) ) {
                cp_labels.erase( cp_labels.begin() + i );
                control_points->erase( control_points->begin() + i );
            }
        }
        for ( int i = 0; i < cp_labels.size(); ++i ) {
            cp_labels[i]->id = i;
            cp_labels[i]->label.setText( "P" + juce::String( i ) + ": ", juce::dontSendNotification );
        }
    }
}

//==============================================================================
MainComponent::MainComponent() {
    fwindow_width = static_cast< float >( window_width );
    fwindow_height = static_cast< float >( window_height );

    bottom_corner = { fwindow_width * 0.15f, fwindow_height * 0.5f };
    top_corner = { fwindow_width * 0.95f, fwindow_height * 0.05f };

    top_screen_limit = fwindow_height * 0.05f;
    bottom_screen_limit = fwindow_height * ( 1.f - 0.05f );

    top_value_limit = 1.0;
    bottom_value_limit = -1.0;

    Trace::Instance().Message( "Bottom: " + std::to_string( bottom_corner.y ), FILENAME, LINENUMBER );
    Trace::Instance().Message( "Top: " + std::to_string( top_corner.y ), FILENAME, LINENUMBER );

    setSize( window_width, window_height );
    setFramesPerSecond( 144 );

    side_panel.Start( this, &control_points, window_height, padding );

    addAndMakeVisible( side_panel.GetHideButton() );
    addAndMakeVisible( side_panel.GetAddButton() );
    addAndMakeVisible( side_panel.GetExportButton() );

    for ( unsigned i = 0; i < 8; ++i ) {
        control_points.push_back( std::make_shared< ControlPoint >( 0.0 ) );
        side_panel.AddLabel();
    }

    precompute_bb_values();
}

void MainComponent::precompute_bb_values() {
    for ( unsigned i = 0; i < max_control_points; ++i ) {
        bb_values.push_back( std::vector< double >( max_control_points, 1.0 ) );
    }

    unsigned value_per_row = 1;

    for ( unsigned i = 2; i < max_control_points; ++i ) {
        for ( unsigned j = 1; j < max_control_points; ++j ) {
            bb_values[i][j] = bb_values[i - 1][j - 1] + bb_values[i - 1][j];
            if ( j >= value_per_row )
                break;
        }
        value_per_row += 1;
    }
}

//==============================================================================
void MainComponent::update() {
    if ( !selected_control_point )
        return;

    selected_control_point->time_since_selected += ( 1.0 / 60.0 );

    double t = selected_control_point->time_since_selected / selected_control_point->time_to_animate_when_selected;

    double new_radius = ( 1.0 - t ) * ( selected_control_point->outer_radius / 4.0 ) + ( t )*selected_control_point->outer_radius;
    selected_control_point->inner_radius = std::clamp( new_radius, selected_control_point->outer_radius / 4.0, selected_control_point->outer_radius );
}

void MainComponent::paint( juce::Graphics& g ) {
    g.fillAll( juce::Colour( 0xffffffff ) );

    // Small lines
    g.setColour( juce::Colour( 0xffe0e0e0 ) );

    float interval_lines = ( top_corner.x - bottom_corner.x ) * 0.05f * 0.2f;
    float counter = bottom_corner.x - ( 20.f * interval_lines );
    while ( counter < ( fwindow_width ) ) {
        g.fillRect( counter, 0.f, 0.9f, fwindow_height );
        counter += interval_lines;
    }

    interval_lines = ( bottom_corner.y - top_corner.y ) * 0.1f * 0.2f;
    counter = bottom_corner.y + ( 100.f * interval_lines );
    while ( counter > 0 ) {
        g.fillRect( 0.f, counter, fwindow_width, 0.9f );
        counter -= interval_lines;
    }

    // Mid lines
    g.setColour( juce::Colour( 0xff999999 ) );

    interval_lines = ( top_corner.x - bottom_corner.x ) * 0.05f;
    counter = bottom_corner.x - ( 4.f * interval_lines );
    while ( counter < ( fwindow_width ) ) {
        g.fillRect( counter, 0.f, 1.f, fwindow_height );

        float calculated_value = ( counter - bottom_corner.x ) / ( ( fwindow_width * 0.95f ) - bottom_corner.x );
        juce::String value = juce::String::toDecimalStringWithSignificantFigures( calculated_value, 2 );
        g.drawText( value, static_cast< int >( counter - fwindow_width * 0.025f ),
                    static_cast< int >( bottom_corner.y ), static_cast< int >( fwindow_width * 0.025f ),
                    static_cast< int >( fwindow_height * 0.025f ), juce::Justification::centred );
        counter += interval_lines;
    }

    interval_lines = ( bottom_corner.y - top_corner.y ) * 0.1f;
    counter = bottom_corner.y + ( 20.f * interval_lines );
    while ( counter > 0 ) {
        g.fillRect( 0.f, counter, fwindow_width, 1.f );
        float calculated_value = 1.f - ( ( counter - top_corner.y ) / ( bottom_corner.y - top_corner.y ) );
        if ( calculated_value >= 0.1 || calculated_value <= -0.1 ) {
            juce::String value = juce::String::toDecimalStringWithSignificantFigures( calculated_value, 2 );
            g.drawText( value, static_cast< int >( bottom_corner.x - ( fwindow_width * 0.025f ) ),
                        static_cast< int >( counter ), static_cast< int >( fwindow_width * 0.025f ),
                        static_cast< int >( fwindow_height * 0.025f ), juce::Justification::centred );
        }
        counter -= interval_lines;
    }

    // Main grid line (vertical)
    g.setColour( juce::Colour( 0xff191919 ) );
    g.fillRect( bottom_corner.x, 0.f, 2.f, fwindow_height );

    // Main grid line (horizontal)
    g.setColour( juce::Colour( 0xff191919 ) );
    g.fillRect( 0.f, bottom_corner.y, fwindow_width, 2.f );

    unsigned cp_count = static_cast< unsigned >( control_points.size() );
    if ( cp_count >= 2 ) {

        juce::Path bezier_curve_path;
        bezier_curve_path.startNewSubPath( juce::Point< float >{ static_cast< float >( ( ( top_corner.x - bottom_corner.x ) * ( 0.0 ) ) + bottom_corner.x ),
                                                                 static_cast< float >( -( bottom_corner.y * control_points[0]->value ) + ( top_corner.y * control_points[0]->value ) + bottom_corner.y ) } );

        float t = 0.f;
        double last = 0.f;
        while ( t < 1.f ) {
            double result = 0.0;
            for ( unsigned i = 0; i < cp_count; ++i ) {
                result += control_points[i]->value * bb_values[cp_count - 1][i] * pow( 1 - t, cp_count - 1 - i ) * pow( t, i );
            }

            juce::Point< double > new_point = { ( ( top_corner.x - bottom_corner.x ) * ( t ) ) + bottom_corner.x,
                                                -( bottom_corner.y * result ) + ( top_corner.y * result ) + bottom_corner.y };
            last = new_point.y;
            bezier_curve_path.lineTo( { static_cast< float >( new_point.x ), static_cast< float >( new_point.y ) } );
            t += 0.001f;
        }

        g.strokePath( bezier_curve_path, juce::PathStrokeType( 3.f ) );
    }

    int i = 0;
    for ( std::shared_ptr< ControlPoint > control_point : control_points ) {
        g.setColour( juce::Colour( Color_List[i % 10] ) );

        juce::Point< float > position = { ( ( top_corner.x - bottom_corner.x ) * ( static_cast< float >( i ) / static_cast< float >( control_points.size() - 1 ) ) ) + bottom_corner.x,
                                          -( bottom_corner.y * control_point->GetValueF() ) + ( top_corner.y * control_point->GetValueF() ) + bottom_corner.y };
        control_point->paint( g, position );
        ++i;
    }
    side_panel.draw( g );
}

void MainComponent::resized() {
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    window_width = getWidth();
    window_height = getHeight();

    fwindow_width = static_cast< float >( window_width );
    fwindow_height = static_cast< float >( window_height );

    bottom_corner = { fwindow_width * 0.15f, fwindow_height * 0.5f };
    top_corner = { fwindow_width * 0.95f, fwindow_height * 0.05f };

    top_screen_limit = fwindow_height * 0.05f;
    bottom_screen_limit = fwindow_height * ( 1.f - 0.05f );
}

//==============================================================================
void MainComponent::mouseDown( const juce::MouseEvent& event ) {
    juce::Point< double > mouse_position{ static_cast< double >( event.position.x ), static_cast< double >( event.position.y ) };

    for ( std::shared_ptr< ControlPoint > control_point : control_points ) {
        double distance = std::pow( control_point->position.x - mouse_position.x, 2 ) +
                          std::pow( mouse_position.y - control_point->position.y, 2 );

        if ( distance <= std::pow( control_point->outer_radius, 2 ) ) {
            control_point->selected = true;
            control_point->time_since_selected = 0.0;

            selected_control_point = control_point;
            return;
        }
    }

    if ( control_points.size() >= max_control_points )
        return;

    // control_points.push_back( ControlPoint( mouse_position ) );
}

void MainComponent::mouseUp( const juce::MouseEvent& ) {
    if ( !selected_control_point )
        return;

    selected_control_point->selected = false;
    selected_control_point->inner_radius = selected_control_point->outer_radius / 4.0;
    selected_control_point = nullptr;
}

void MainComponent::mouseDrag( const juce::MouseEvent& event ) {
    if ( !selected_control_point )
        return;

    juce::Point< double > mouse_position{ static_cast< double >( event.position.x ), static_cast< double >( event.position.y ) };

    juce::Point< double > new_control_point_position{ selected_control_point->position.x,
                                                      std::clamp< double >( mouse_position.y, padding, static_cast< double >( window_height - padding ) ) };

    selected_control_point->value = 1.f - ( ( new_control_point_position.y - top_corner.y ) / ( bottom_corner.y - top_corner.y ) );
}

unsigned MainComponent::GetMaxControlPoints() const {
    return max_control_points;
}

ControlPoint& MainComponent::GetControlPoint( unsigned index ) {
    return *control_points[index];
}
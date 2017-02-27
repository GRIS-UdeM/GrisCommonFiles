/*
 ==============================================================================
 
 This file is part of the JUCE library.
 Copyright (c) 2015 - ROLI Ltd.
 
 Permission is granted to use this software under the terms of either:
 a) the GPL v2 (or any later version)
 b) the Affero GPL v3
 
 Details of these licenses can be found at: www.gnu.org/licenses
 
 JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 
 ------------------------------------------------------------------------------
 
 To release a closed-source product which uses JUCE, commercial licenses are
 available: visit www.juce.com for more information.
 
 ==============================================================================
 */

#ifndef GRISLOOKANDFEEL_H_INCLUDED
#define GRISLOOKANDFEEL_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/** Custom Look And Feel subclasss.
 
 Simply override the methods you need to, anything else will be inherited from the base class.
 It's a good idea not to hard code your colours, use the findColour method along with appropriate
 ColourIds so you can set these on a per-component basis.
 */




class GrisLookAndFeel    : public LookAndFeel_V3 {
private:
    
    float m_fFontSize;

    Font  m_Font = Font(juce::CustomTypeface::createSystemTypefaceFor(BinaryData::SinkinSans400Regular_otf, (size_t) BinaryData::SinkinSans400Regular_otfSize));

    Colour m_BackGroundAndFieldColour;
    Colour m_WinBackGroundAndFieldColour;
    Colour m_LightColour, m_DarkColour, m_GreyColour, m_Oncolor, m_TextBgcolor,m_OncolorOver,m_OncolorDown,m_Offcolor;
    
public:
    GrisLookAndFeel(){
        m_BackGroundAndFieldColour   = Colours::darkgrey;
        m_WinBackGroundAndFieldColour = Colour::fromRGB(46, 46, 46);
        m_LightColour               = Colours::whitesmoke;
        m_DarkColour                = Colours::black;
        m_GreyColour                = Colours::grey;
        
        m_Oncolor                   = Colour::fromRGB(255, 165, 25);
        m_OncolorOver               = Colour::fromRGB(255, 184, 75);
        m_OncolorDown               = Colour::fromRGB(222, 144, 22);
        
        m_Offcolor                   = Colour::fromRGB(46, 46, 46);
       
        
        m_TextBgcolor               = Colour::fromRGB(172, 172, 172);
        
        setColour(PopupMenu::highlightedBackgroundColourId, m_Oncolor);
        setColour(TextEditor::backgroundColourId, m_TextBgcolor);
        setColour(TextEditor::highlightColourId, m_Oncolor);
        setColour(TextEditor::shadowColourId, m_TextBgcolor);
        
        
        setColour(ComboBox::backgroundColourId, m_TextBgcolor);
        setColour(ComboBox::outlineColourId, m_TextBgcolor);
        
        setColour(Slider::thumbColourId, m_LightColour);
        setColour(Slider::rotarySliderFillColourId, m_Oncolor);
        setColour(Slider::trackColourId, m_DarkColour);
        setColour(Slider::textBoxBackgroundColourId, m_TextBgcolor);
        setColour(Slider::textBoxOutlineColourId, Colours::transparentBlack);
        
        
        
#if WIN32
        m_fFontSize = 18.f;
#else
        m_fFontSize = 10.f;
#endif
        m_Font.setHeight(m_fFontSize);
       
    }
    
    Font getFont(){
        return m_Font;
    }
    Font getLabelFont (Label & label) override{
        return m_Font;
    }
    Font getComboBoxFont (ComboBox & comboBox) override{
        return m_Font;
    }
    Font getTextButtonFont (TextButton &, int buttonHeight) override{
        return m_Font;
    }
    Font getMenuBarFont	(MenuBarComponent &, int itemIndex, const String & itemText) override{
        return m_Font;
    }
    
    Colour getWinBackgroundColour(){
        return m_WinBackGroundAndFieldColour;
    }

    Colour getBackgroundColour(){
        return m_BackGroundAndFieldColour;
    }
    
    Colour getFieldColour(){
        return m_BackGroundAndFieldColour;
    }
    
    Colour getFontColour(){
        return m_LightColour;
    }
    
    Colour getScrollBarColour(){
        return m_GreyColour;
    }
    
    Colour getDarkColour(){
        return m_DarkColour;
    }
    
    Colour getLightColour(){
        return m_LightColour;
    }
    
    //https://github.com/audioplastic/Juce-look-and-feel-examples/blob/master/JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel.cpp
    
    void drawComboBox(Graphics& g,int width, int height,bool isButtonDown,int buttonX,int buttonY,int buttonW,int buttonH,ComboBox & box) override
    {
        box.setColour(ColourSelector::backgroundColourId, m_Oncolor);
    

        g.fillAll (m_TextBgcolor);//box.findColour (ComboBox::backgroundColourId))
        
        const Colour buttonColour (m_DarkColour);//box.findColour (ComboBox::buttonColourId)
        const float arrowX = 0.3f;
        const float arrowH = 0.2f;
        
        Path p;
        p.addTriangle (buttonX + buttonW * 0.5f,            buttonY + buttonH * (0.45f - arrowH),
                       buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.45f,
                       buttonX + buttonW * arrowX,          buttonY + buttonH * 0.45f);
        
        p.addTriangle (buttonX + buttonW * 0.5f,            buttonY + buttonH * (0.55f + arrowH),
                       buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.55f,
                       buttonX + buttonW * arrowX,          buttonY + buttonH * 0.55f);
        
        g.setColour (m_DarkColour.withMultipliedAlpha (box.isEnabled() ? 1.0f : 0.3f));//box.findColour (ComboBox::arrowColourId)
        g.fillPath (p);
    }
    
    void drawRoundThumb (Graphics& g, const float x, const float y, const float diameter, const Colour& colour, float outlineThickness) {
        const juce::Rectangle<float> a (x, y, diameter, diameter);
        const float halfThickness = outlineThickness * 0.5f;
        
        Path p;
        p.addEllipse (x + halfThickness, y + halfThickness, diameter - outlineThickness, diameter - outlineThickness);
        
        const DropShadow ds (m_DarkColour, 1, Point<int> (0, 0));
        ds.drawForPath (g, p);
        
        g.setColour (colour);
        g.fillPath (p);
        
        g.setColour (colour.brighter());
        g.strokePath (p, PathStrokeType (outlineThickness));
    }
    
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override {
        
        const float width  = button.getWidth() - 1.0f;
        const float height = button.getHeight() - 1.0f;
        const float cornerSize = jmin (15.0f, jmin (width, height) * 0.45f);
        const float lineThickness = cornerSize * 0.1f;
        const float halfThickness = lineThickness * 0.5f;
        Path outline;
        outline.addRectangle(0.5f + halfThickness, 0.5f + halfThickness, width - lineThickness, height - lineThickness);
        g.setColour (m_TextBgcolor);
        if (isButtonDown || isMouseOverButton){
            g.setColour (m_OncolorOver);
        }
        if ( button.getToggleState()) {
            g.setColour (m_Oncolor);//outlineColour

        }
        if(button.isEnabled() && button.isMouseButtonDown()){
            g.setColour (m_OncolorDown);
        }
        g.fillPath (outline);
    }
    
    
    void drawTickBox (Graphics& g, Component& component, float x, float y, float w, float h, bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown) override {
        const float boxSize = w * 0.8f;
        const Rectangle<float> r (x, y + (h - boxSize) * 0.5f, boxSize, boxSize);

        if (ticked) {
            Colour colour = m_Oncolor;
            
            if(component.isMouseOver()){
                colour = m_OncolorOver;
            }
            
            if(!component.isEnabled()){
                colour = m_Oncolor.withBrightness(0.3f);
            }
            g.setColour (colour);
            g.fillRect (r);

        }else{
            Colour colour = m_Offcolor;
            if(!component.isEnabled()){
                colour = m_Offcolor.withBrightness(0.3f);
            }
            g.setColour (colour);
            g.fillRect (r);
        }
        
        if(component.isEnabled() && component.isMouseButtonDown()){
            g.setColour (m_OncolorDown);
            g.fillRect (r);
        }
    }
    
    
    void drawLinearSliderThumb (Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider) override {
        const float sliderRadius = (float) (getSliderThumbRadius (slider) - 2);
        float kx, ky;
        
        if (style == Slider::LinearVertical) {
            kx = x + width * 0.5f;
            ky = sliderPos;
        } else {
            kx = sliderPos;
            ky = y + height * 0.5f;
        }
        const Rectangle<float> r (kx - (sliderRadius/2.0f), ky- sliderRadius , 6, height*2.0f);

        if(slider.isEnabled()){
            Colour colour = m_Oncolor;
            
            if(slider.isMouseOver()){
                colour = m_OncolorOver;
            }
            if(slider.isMouseButtonDown()){
                colour = m_OncolorDown;
            }
            g.setColour (colour);
            g.fillRect (r);
        }else{
            g.setColour (m_Offcolor);
            g.fillRect (r);
        }
        
    }
    
    void drawLinearSlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider) override {
        drawLinearSliderBackground (g, x, y, width, height+2, sliderPos, minSliderPos, maxSliderPos, style, slider);
        drawLinearSliderThumb (g, x, y, width, height+2, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
    
    void drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height, float /*sliderPos*/, float /*minSliderPos*/, float /*maxSliderPos*/, const Slider::SliderStyle /*style*/, Slider& slider) override {
        const float sliderRadius = getSliderThumbRadius (slider) - 5.0f;
        Path on, off;

        if (slider.isHorizontal()) {
            const float iy = y + height * 0.5f - sliderRadius * 0.5f;
            juce::Rectangle<float> r (x - sliderRadius * 0.5f, iy, width + sliderRadius, sliderRadius);
            const float onW = r.getWidth() * ((float) slider.valueToProportionOfLength (slider.getValue()));
            on.addRectangle (r.removeFromLeft (onW));
            off.addRectangle (r);
        } else {
            const float ix = x + width * 0.5f - sliderRadius * 0.5f;
            juce::Rectangle<float> r (ix, y - sliderRadius * 0.5f, sliderRadius, height + sliderRadius);
            const float onH = r.getHeight() * ((float) slider.valueToProportionOfLength (slider.getValue()));
            on.addRectangle (r.removeFromBottom (onH));
            off.addRectangle (r);
        }
        
        if (slider.isEnabled()){
            g.setColour (slider.findColour (Slider::rotarySliderFillColourId));
            g.fillPath (on);
            g.setColour (slider.findColour (Slider::trackColourId));
            g.fillPath (off);
        }else{
            g.setColour (m_Offcolor);
            g.fillPath (on);
            g.fillPath (off);
        }
       
    }
    
    void fillTextEditorBackground(Graphics& g, int width, int height, TextEditor& t) override {
        g.setColour(m_TextBgcolor);
        g.fillAll();
    }
    
    void drawTextEditorOutline(Graphics& g, int width, int height, TextEditor& t) override {
        if(t.isMouseOver())
        {
            g.setColour(m_Oncolor);
            g.drawRect (0, 0, width, height);
        }
       
    }
    
    void drawToggleButton (Graphics& g, ToggleButton& button, bool isMouseOverButton, bool isButtonDown) override {
        if (button.hasKeyboardFocus (true))
        {
            g.setColour (button.findColour (TextEditor::focusedOutlineColourId));
            //g.drawRect (0, 0, button.getWidth(), button.getHeight());
        }
        
        float fontSize = jmin (15.0f, button.getHeight() * 0.75f);
        const float tickWidth = fontSize * 1.1f;
        
        drawTickBox (g, button, 4.0f, (button.getHeight() - tickWidth) * 0.5f,
                     tickWidth, tickWidth,
                     button.getToggleState(),
                     button.isEnabled(),
                     isMouseOverButton,
                     isButtonDown);
        
        g.setColour(button.findColour (ToggleButton::textColourId));
        g.setFont(m_Font);
        
        if (! button.isEnabled())
            g.setOpacity (0.5f);
        
        const int textX = (int) tickWidth + 5;
        
        g.drawFittedText (button.getButtonText(),
                          textX, 0,
                          button.getWidth() - textX - 2, button.getHeight(),
                          Justification::centredLeft, 10);
    }
    
    void drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown) override{
        const Rectangle<int> activeArea (button.getActiveArea());
        activeArea.withHeight(18);
        const TabbedButtonBar::Orientation o = button.getTabbedButtonBar().getOrientation();
        const Colour bkg (button.getTabBackgroundColour());
        
        if (button.getToggleState())
        {
            g.setColour (bkg);
        }
        else
        {
            g.setColour (bkg.brighter (0.1f));
        }
        
        g.fillRect (activeArea);
        
        g.setColour (m_WinBackGroundAndFieldColour);
        
        Rectangle<int> r (activeArea);
        if (o != TabbedButtonBar::TabsAtTop)      g.fillRect (r.removeFromBottom (1));
            if (o != TabbedButtonBar::TabsAtRight)    g.fillRect (r.removeFromLeft (1));
                if (o != TabbedButtonBar::TabsAtLeft)     g.fillRect (r.removeFromRight (1));
        
        const float alpha = button.isEnabled() ? ((isMouseOver || isMouseDown) ? 1.0f : 0.8f) : 0.3f;
        Colour col = (bkg.contrasting().withMultipliedAlpha (alpha));
        const Rectangle<float> area (button.getTextArea().toFloat());
        
        float length = area.getWidth();
        float depth  = area.getHeight();
        
        if (button.getTabbedButtonBar().isVertical())
            std::swap (length, depth);
            
        TextLayout textLayout;
        createTabTextLayout (button, length, depth, col, textLayout);
        textLayout.draw (g, Rectangle<float> (length, depth));
        /*
        Rectangle<int> activeArea (button.getActiveArea());

        //const TabbedButtonBar::Orientation o = button.getTabbedButtonBar().getOrientation();
        const Colour bkg (button.getTabBackgroundColour());
        
        if (button.getToggleState())
        {
            g.setColour (bkg);
        }
        else
        {
            g.setColour (bkg.brighter (0.1f));
        }
        
        g.fillRect (activeArea);
        g.setColour (m_WinBackGroundAndFieldColour);
        
        Rectangle<int> r (activeArea);
        const float alpha = button.isEnabled() ? ((isMouseOver || isMouseDown) ? 1.0f : 0.8f) : 0.3f;
        Colour col = (bkg.contrasting().withMultipliedAlpha (alpha));
        
       
        const Rectangle<float> area (button.getTextArea().toFloat());
        
        float length = area.getWidth();
        float depth  = area.getHeight();
        
        if (button.getTabbedButtonBar().isVertical())
            std::swap (length, depth);
        
        TextLayout textLayout;
        createTabTextLayout (button, length, depth, col, textLayout);
        
        AffineTransform t;
        g.addTransform (t);
        textLayout.draw (g, Rectangle<float> (length, depth));*/
    }
    
    void createTabTextLayout (const TabBarButton& button, float length, float depth, Colour colour, TextLayout& textLayout)
    {
        Font font (m_Font);
#if WIN32
        font.setHeight(depth * 0.60f);
#else

        font.setHeight(depth * 0.35f);
#endif
        font.setUnderline (button.hasKeyboardFocus (false));
        
        AttributedString s;
        s.setJustification (Justification::centred);
        s.append (button.getButtonText().trim(), font, colour);
        
        textLayout.createLayout (s, length);
    }
    

    
//    void drawTabButtonText (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown) override
//    {
//        const Rectangle<float> area (button.getTextArea().toFloat());
//        
//        float length = area.getWidth();
//        float depth  = area.getHeight();
//        
//        if (button.getTabbedButtonBar().isVertical())
//            std::swap (length, depth);
//        
//        Font font (m_Font);
//        font.setHeight(depth * 0.35f);
//        font.setUnderline (button.hasKeyboardFocus (false));
//        
//        AffineTransform t;
//        
//        switch (button.getTabbedButtonBar().getOrientation())
//        {
//            case TabbedButtonBar::TabsAtLeft:   t = t.rotated (float_Pi * -0.5f).translated (area.getX(), area.getBottom()); break;
//            case TabbedButtonBar::TabsAtRight:  t = t.rotated (float_Pi *  0.5f).translated (area.getRight(), area.getY()); break;
//            case TabbedButtonBar::TabsAtTop:
//            case TabbedButtonBar::TabsAtBottom: t = t.translated (area.getX(), area.getY()); break;
//            default:                            jassertfalse; break;
//        }
//        
//        Colour col;
//        
//        if (button.isFrontTab() && (button.isColourSpecified (TabbedButtonBar::frontTextColourId)
//                                    || isColourSpecified (TabbedButtonBar::frontTextColourId)))
//            col = findColour (TabbedButtonBar::frontTextColourId);
//        else if (button.isColourSpecified (TabbedButtonBar::tabTextColourId)
//                 || isColourSpecified (TabbedButtonBar::tabTextColourId))
//            col = findColour (TabbedButtonBar::tabTextColourId);
//        else
//            col = button.getTabBackgroundColour().contrasting();
//        
//        const float alpha = button.isEnabled() ? ((isMouseOver || isMouseDown) ? 1.0f : 0.8f) : 0.3f;
//        
//        g.setColour (col.withMultipliedAlpha (alpha));
//        g.setFont (font);
//        g.addTransform (t);
//        
//        g.drawFittedText (button.getButtonText().trim(),
//                          0, 0, (int) length, (int) depth,
//                          Justification::centred,
//                          jmax (1, ((int) depth) / 12));
//    }
    

        
        //    //we don't use those, so far
        //    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override {
        //        const float radius = jmin (width / 2, height / 2) - 2.0f;
        //        const float centreX = x + width * 0.5f;
        //        const float centreY = y + height * 0.5f;
        //        const float rx = centreX - radius;
        //        const float ry = centreY - radius;
        //        const float rw = radius * 2.0f;
        //        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        //        const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
        //
        //        if (slider.isEnabled())
        //            g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
        //        else
        //            g.setColour (Colour (0x80808080));
        //
        //        {
        //            Path filledArc;
        //            filledArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, angle, 0.0);
        //            g.fillPath (filledArc);
        //        }
        //
        //        {
        //            const float lineThickness = jmin (15.0f, jmin (width, height) * 0.45f) * 0.1f;
        //            Path outlineArc;
        //            outlineArc.addPieSegment (rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, 0.0);
        //            g.strokePath (outlineArc, PathStrokeType (lineThickness));
        //        }
        //    }
};
        
#endif
        

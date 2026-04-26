#include "SettingsMenu.h"
#include <iostream>

SettingsMenu::SettingsMenu(const sf::Font& font, int resolutionIndex, int testIndex)
    : m_title(font, "Settings", m_titleTextColor, m_titleYSizeFraction)
    , m_backButton(font, "Back", {m_settingWidth, m_settingHeight}, m_buttonXMargin, m_buttonYMargin,
                   m_buttonBgColor, m_buttonHvBgColor, m_buttonTextColor, m_buttonHvTextColor, m_buttonOlColor)
{
    m_title.setOutlineThickness(3);
    std::vector<std::string> resolutions = {
        "1920x1080",
        "1440x900",
        "1024x900",
        "900x900"
    };
    // keeping note above for future settigns labels (need to add offset not included in the first setting
    SettingItem resolutionItem = {
        MenuLabel(font, "Resolution", m_buttonTextColor, m_settingHeight),
        Dropdown(font, resolutions, {m_settingWidth, m_settingHeight}, m_buttonXMargin, m_buttonYMargin,
                 m_buttonBgColor, m_buttonHvBgColor, m_buttonTextColor, m_buttonHvTextColor, m_buttonOlColor)
    };
    resolutionItem.dropdown.setSelectedIndex(resolutionIndex);
    m_settingsItems.push_back(resolutionItem);

    std::vector<std::string> testers = {
        "test1",
        "test2",
        "test3",
        "test4"
    };
    SettingItem testItem = {
        MenuLabel(font, "Testing", m_buttonTextColor, m_settingHeight),
        Dropdown(font, testers, {m_settingWidth, m_settingHeight}, m_buttonXMargin, m_buttonYMargin,
                 m_buttonBgColor, m_buttonHvBgColor, m_buttonTextColor, m_buttonHvTextColor, m_buttonOlColor)
    };
    testItem.dropdown.setSelectedIndex(testIndex);
    m_settingsItems.push_back(testItem);
}
bool SettingsMenu::inDropdown(){
    for(auto& settingsItem : m_settingsItems){
        if(settingsItem.dropdown.isOpen()){
            return true;
        }
    }
    return false;
}
int SettingsMenu::getDropdownSize(){
    for(auto& settingsItem : m_settingsItems){
        if(settingsItem.dropdown.isOpen()){
            return settingsItem.dropdown.getSize();
        }
    }
    // return -1 if not in a dropdown
    return -1;
}
int SettingsMenu::getActiveDropdownIndex(){
    for(size_t i = 0; i < m_settingsItems.size(); i++){
        if(m_settingsItems[i].dropdown.isOpen()){
            return i;
        }
    }
    // return -1 if not in a dropdown
    return -1;
}
void SettingsMenu::setSelection(int selection){
    m_selection = selection;
}
int SettingsMenu::getSelection(){
    return m_selection;
}
void SettingsMenu::incSelection(){
    m_selection++;
    if(!inDropdown()){
        // +1 for back button
        if(m_selection >= static_cast<int>(m_settingsItems.size() + 1)){
            m_selection = 0;
        }
    }
    else{
        int selectedDD = getActiveDropdownIndex();
        if(m_selection >= static_cast<int>(m_settingsItems[selectedDD].dropdown.getSize())){
            m_selection = 0;
        }
    }
    // std::cout << "Current Selection Index: " << m_selection << std::endl;
}
void SettingsMenu::decSelection(){
    m_selection--;
    if(!inDropdown()){
        if(m_selection < 0){
            // place on back button if going above top option
            m_selection = static_cast<int>(m_settingsItems.size());
        }
    }
    else{
        int selectedDD = getActiveDropdownIndex();
        if(m_selection < 0){
            m_selection = static_cast<int>(m_settingsItems[selectedDD].dropdown.getSize()) - 1;
        }
    }
    // std::cout << "Current Selection Index: " << m_selection << std::endl;
}

void SettingsMenu::handleClick(sf::Vector2i mousePos){
    if(inDropdown()){
        int selectedDD = getActiveDropdownIndex();
        m_settingsItems[selectedDD].dropdown.handleClick(mousePos);
    }
    else{
        for(auto& setting : m_settingsItems){
            setting.dropdown.handleClick(mousePos);
            // reset the selection to 0 if openeing a dd menu
            if(inDropdown()) m_selection = 0;
        }

        if(m_backButton.isHovered(mousePos)){
            m_shouldGoBack = true;
        }
    }
}
void SettingsMenu::handleInteract(){
    if(!inDropdown()){
        if(m_selection < static_cast<int>(m_settingsItems.size())){
            m_settingsItems[m_selection].dropdown.toggle();
            m_selection = 0;
        }
        else{
            m_shouldGoBack = true;
        }
    }
    else{
        int selectedDD = getActiveDropdownIndex();

        m_settingsItems[selectedDD].dropdown.select(m_selection);
        m_settingsItems[selectedDD].dropdown.close();
        m_selection = selectedDD;
    }
}
void SettingsMenu::closeDropdown(int ddIndex){
    if(!inDropdown()) return;
    m_settingsItems[ddIndex].dropdown.close();
    m_selection = ddIndex;
}

int SettingsMenu::getResolutionIndex() const{
    return m_settingsItems[0].dropdown.getSelectedIndex();
}
int SettingsMenu::getTestIndex() const{
    return m_settingsItems[1].dropdown.getSelectedIndex();
}
bool SettingsMenu::shouldGoBack(){
    return m_shouldGoBack;
}

void SettingsMenu::update(sf::Vector2i mousePos, InputSystem& inputSystem){
    // update the option selection if needed (keyboard input)
    if(inputSystem.isNewlyPressed(Button::Up)){
        decSelection();
    }else if(inputSystem.isNewlyPressed(Button::Down) || inputSystem.isNewlyPressed(Button::Tab)){
        incSelection();
    }

    if(!inDropdown()){
        // change selection if mouse is hovering an option (outside of dropdown)
        for(size_t i = 0; i < m_settingsItems.size(); i++){
            if(m_settingsItems[i].dropdown.isHovered(mousePos)){
                m_selection = i;
            }
            if(m_backButton.isHovered(mousePos)){
                m_selection = m_settingsItems.size();
            }
        }

        // hover/unhover the options
        if(m_selection == static_cast<int>(m_settingsItems.size())){
            m_backButton.hover();
            for(size_t i = 0; i < m_settingsItems.size(); i++){
                m_settingsItems[i].dropdown.unhover();
            }
        }
        else{
            for(size_t i = 0; i < m_settingsItems.size(); i++){
                if(static_cast<int>(i) == m_selection){
                    m_settingsItems[i].dropdown.hover(-1);
                }
                else{
                    m_settingsItems[i].dropdown.unhover();
                }
            }
            m_backButton.unhover();
        }
    }
    else{ // in dropdown
        int selectedDD = getActiveDropdownIndex();
        // change selection if mouse is hovering an option (inside of dropdown)
        for(int i = 0; i < m_settingsItems[selectedDD].dropdown.getSize(); i++){
            if(m_settingsItems[selectedDD].dropdown.getBoxes()[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))){
                m_selection = i;
            }
        }
        // hover/unhover the options
        m_settingsItems[selectedDD].dropdown.hover(m_selection);
        m_backButton.unhover();
    }
}
void SettingsMenu::updateLayout(sf::Vector2u windowSize){
    m_title.updateLayout(windowSize, m_titlePosFraction.x, m_titlePosFraction.y);
    for(size_t i = 0; i < m_settingsItems.size(); i++){
        m_settingsItems[i].label.updateLayout(windowSize, m_settingLabelFirstXposFraction,
                                              m_settingItemFirstYposFraction + (i * (m_settingItemYposMargin + m_settingHeight)));
        m_settingsItems[i].dropdown.updateLayout(windowSize, m_settingDropdownFirstXposFraction, 
                                                 m_settingItemFirstYposFraction + (i * (m_settingItemYposMargin + m_settingHeight)));
    }
    // m_backButton.updateLayout(windowSize, m_settingDropdownFirstXposFraction, m_backButtonYPosFraction);
    m_backButton.updateLayout(windowSize, m_backButtonPosFraction.x, m_backButtonPosFraction.y);
}
void SettingsMenu::render(sf::RenderWindow &window){
    m_title.render(window);
    m_backButton.render(window);
    if(inDropdown()){
        int selectedDD = getActiveDropdownIndex();
        for(size_t i = 0; i < m_settingsItems.size(); i++){
            if(static_cast<int>(i) != selectedDD){
                m_settingsItems[i].label.render(window);
                m_settingsItems[i].dropdown.render(window);
            }
        }
        // render the selected dropdown after other options so options don't get covered
        m_settingsItems[selectedDD].label.render(window);
        m_settingsItems[selectedDD].dropdown.render(window);
    }
    else{
        for(size_t i = 0; i < m_settingsItems.size(); i++){
            m_settingsItems[i].label.render(window);
            m_settingsItems[i].dropdown.render(window);
        }
    }
}

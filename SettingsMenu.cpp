#include "SettingsMenu.h"

SettingsMenu::SettingsMenu(const sf::Font& font)
    : m_title(font, "Settings", m_titleTextColor, m_titlePosFraction, m_titleYSizeFraction)
    , m_backButton(font, "Back", {m_settingWidth, m_settingHeight}, m_buttonXMargin, m_buttonYMargin,
                   m_buttonBgColor, m_buttonHvBgColor, m_buttonTextColor, m_buttonHvTextColor, m_buttonOlColor)
{
    std::vector<std::string> resolutions = {
        "1920x1080",
        "1440x900",
        "1024x900",
        "900x900"
    };
    SettingItem resolutionItem = {
        MenuLabel(font, "Resolution", m_buttonTextColor,
                  {m_settingLabelFirstXposFraction, m_settingItemFirstYposFraction},
                  m_settingHeight),
        Dropdown(font, resolutions, {m_settingWidth, m_settingHeight}
                 ,m_buttonBgColor, m_buttonHvBgColor, m_buttonTextColor, m_buttonHvTextColor, m_buttonOlColor)
    };
    m_settingsItems.push_back(resolutionItem);
}
// 0 if not in dropdown, or the size of the dropdown
int SettingsMenu::inDropdown(){
    for(auto& settingsItem : m_settingsItems){
        if(settingsItem.dropdown.isOpen() != 0){
            return settingsItem.dropdown.isOpen();
        }
    }
    return 0;
}
int SettingsMenu::getSelection(){
    return m_selection;
}
void SettingsMenu::incSelection(){
    m_selection++;
    int ddSize = inDropdown();
    if(ddSize == 0){ // not in dropdown
        if(m_selection >= static_cast<int>(m_settingsItems.size())) m_selection = 0;
    }
    else{ // in dropdown
        // get which dropdown we're in
        int selectedDD = 0;
        for(int i = 0; i < m_settingsItems.size(); i++){
            if(m_settingsItems[i].dropdown.isOpen() != 0){
                selectedDD = i;
            }
        }
        if(m_selection >= static_cast<int>(m_settingsItems[selectedDD].dropdown.getSize())){
            m_selection = 0;
        }
    }
}
void SettingsMenu::decSelection(){
    m_selection--;
    int ddSize = inDropdown();
    if(ddSize == 0){ // not in dropdown
        if(m_selection < 0) m_selection = static_cast<int>(m_settingsItems.size()) - 1;
    }
    else{ // in dropdown
        // get which dropdown we're in
        int selectedDD = 0;
        for(int i = 0; i < m_settingsItems.size(); i++){
            if(m_settingsItems[i].dropdown.isOpen() != 0){
                selectedDD = i;
            }
        }
        if(m_selection < 0){
            m_selection = static_cast<int>(m_settingsItems[selectedDD].dropdown.getSize()) - 1;
        }
    }
}
void SettingsMenu::handleClick(sf::Vector2i mousePos){
    for(auto& setting : m_settingsItems){
        setting.dropdown.handleClick(mousePos);
    }

    if(m_backButton.isHovered(mousePos)){
        m_shouldGoBack = true;
    }
}

int SettingsMenu::getResolutionIndex() const{
    return m_settingsItems[0].dropdown.getSelectedIndex();
}
bool SettingsMenu::shouldGoBack(){
    return m_shouldGoBack;
}

void SettingsMenu::update(sf::Vector2i mousePos, InputSystem& inputSystem){
    // update the option selection if needed
    if(inputSystem.isNewlyPressed(Button::Up)){
        decSelection();
    }else if(inputSystem.isNewlyPressed(Button::Down) || inputSystem.isNewlyPressed(Button::Tab)){
        incSelection();
    }

    int ddSize = inDropdown();
    if(ddSize == 0){ // not in dropdown
        for(int i = 0; i < m_settingsItems.size(); i++){
            if(i == m_selection){
                m_settingsItems[i].dropdown.hover(0);
            }
            else{
                m_settingsItems[i].dropdown.unhover();
            }
        }
    }
    else{ // in dropdown
        // get which dropdown we're in
        int selectedDD = 0;
        for(int i = 0; i < m_settingsItems.size(); i++){
            m_settingsItems[i].dropdown.unhover();
            if(m_settingsItems[i].dropdown.isOpen() != 0){
                selectedDD = i;
            }
        }
        for(int i = 0; i < m_settingsItems[selectedDD].dropdown.getSize(); i++){
            if(i == m_selection){
                m_settingsItems[selectedDD].dropdown.hover(i);
            }
        }
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
    m_backButton.updateLayout(windowSize, m_settingDropdownFirstXposFraction, m_backButtonYPosFraction);
}
void SettingsMenu::render(sf::RenderWindow &window){
    m_title.render(window);
    for(size_t i = 0; i < m_settingsItems.size(); i++){
        m_settingsItems[i].label.render(window);
        m_settingsItems[i].dropdown.render(window);
    }
    m_backButton.render(window);
}

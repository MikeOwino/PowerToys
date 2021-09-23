﻿#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "MainWindow.g.h"
#include "RegExShortcut.h"
#include "ExplorerItem.h"
#include "ExplorerItemTemplateSelector.h"

namespace winrt::PowerRenameUI_new::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();

        Windows::Foundation::Collections::IObservableVector<hstring> SearchMRU();
        Windows::Foundation::Collections::IObservableVector<hstring> ReplaceMRU();
        winrt::Windows::Foundation::Collections::IObservableVector<PowerRenameUI_new::ExplorerItem> ExplorerItems();
        winrt::Windows::Foundation::Collections::IObservableVector<PowerRenameUI_new::RegExShortcut> SearchRegExShortcuts();
        winrt::Windows::Foundation::Collections::IObservableVector<PowerRenameUI_new::RegExShortcut> FileRegExShortcuts();

        Windows::UI::Xaml::Controls::AutoSuggestBox AutoSuggestBoxSearch();
        Windows::UI::Xaml::Controls::AutoSuggestBox AutoSuggestBoxReplace();

        Windows::UI::Xaml::Controls::CheckBox ChckBoxRegex();
        Windows::UI::Xaml::Controls::CheckBox ChckBoxCaseSensitive();
        Windows::UI::Xaml::Controls::CheckBox ChckBoxMatchAll();

        Windows::UI::Xaml::Controls::ComboBox ComboBoxRenameParts();

        Windows::UI::Xaml::Controls::Primitives::ToggleButton TglBtnIncludeFiles();
        Windows::UI::Xaml::Controls::Primitives::ToggleButton TglBtnIncludeFolders();
        Windows::UI::Xaml::Controls::Primitives::ToggleButton TglBtnIncludeSubfolders();

        Windows::UI::Xaml::Controls::Primitives::ToggleButton TglBtnUpperCase();
        Windows::UI::Xaml::Controls::Primitives::ToggleButton TglBtnLowerCase();
        Windows::UI::Xaml::Controls::Primitives::ToggleButton TglBtnTitleCase();
        Windows::UI::Xaml::Controls::Primitives::ToggleButton TglBtnCapitalize();

        Windows::UI::Xaml::Controls::Primitives::ToggleButton TglBtnEnumerateItems();

        Windows::UI::Xaml::Controls::Button BtnRename();
        Windows::UI::Xaml::Controls::Button BtnSettings();

        PowerRenameUI_new::ExplorerItem ChangedItem();

        void AddExplorerItem(int32_t id, hstring const& original, hstring const& renamed, int32_t type, int32_t parentId, bool checked);
        void UpdateExplorerItem(int32_t id, hstring const& newName);
        void AppendSearchMRU(hstring const& value);
        void AppendReplaceMRU(hstring const& value);

        void Checked_ids(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void SelectAll(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void btn_showAll_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void btn_showRenamed_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    private:
        PowerRenameUI_new::ExplorerItem m_changedItem{ -1, L"nvm", L"", 0, false };
        PowerRenameUI_new::ExplorerItem FindById(int32_t id);
        PowerRenameUI_new::ExplorerItem FindById(PowerRenameUI_new::ExplorerItem& root, int32_t id);
        void ToggleAll(PowerRenameUI_new::ExplorerItem node, bool checked);

        winrt::Windows::Foundation::Collections::IObservableVector<hstring> m_searchMRU;
        winrt::Windows::Foundation::Collections::IObservableVector<hstring> m_replaceMRU;
        winrt::Windows::Foundation::Collections::IObservableVector<PowerRenameUI_new::ExplorerItem> m_explorerItems;
        winrt::Windows::Foundation::Collections::IObservableVector<PowerRenameUI_new::RegExShortcut> m_searchRegExShortcuts;
        winrt::Windows::Foundation::Collections::IObservableVector<PowerRenameUI_new::RegExShortcut> m_fileRegExShortcuts;
    };
}

namespace winrt::PowerRenameUI_new::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}

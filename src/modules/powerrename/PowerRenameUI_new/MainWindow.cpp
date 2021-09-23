﻿#include "pch.h"
#include "MainWindow.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <winuser.h>

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::PowerRenameUI_new::implementation
{
    MainWindow::MainWindow()
    {
        m_searchMRU = winrt::single_threaded_observable_vector<hstring>();
        m_replaceMRU = winrt::single_threaded_observable_vector<hstring>();

        m_explorerItems = winrt::single_threaded_observable_vector<PowerRenameUI_new::ExplorerItem>();
        m_searchRegExShortcuts = winrt::single_threaded_observable_vector<PowerRenameUI_new::RegExShortcut>();
        m_fileRegExShortcuts = winrt::single_threaded_observable_vector<PowerRenameUI_new::RegExShortcut>();

        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"\\.", L"Matches any character"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"\\d", L"Any digit, short for [0-9]"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"\\D", L"A non-digit, short for [^0-9]"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"\\w", L"A non-whitespace character, short for [^\\s]"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"\\S", L"A word character, short for [a-zA-Z_0-9]"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"\\S+", L"Several non-whitespace characters"));
        m_searchRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"\\b", L"Matches a word boundary where a word character is [a-zA-Z0-9_]."));

        m_fileRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"$YYYY", L"Year"));
        m_fileRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"$MM", L"Month"));
        m_fileRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"$DD", L"Day"));
        m_fileRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"$hh", L"Hours"));
        m_fileRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"$mm", L"Minutes"));
        m_fileRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"$ss", L"Seconds"));
        m_fileRegExShortcuts.Append(winrt::make<PowerRenameUI_new::implementation::RegExShortcut>(L"$fff", L"Milliseconds"));
        InitializeComponent();
    }

    Windows::Foundation::Collections::IObservableVector<hstring> MainWindow::SearchMRU()
    {
        return m_searchMRU;
    }

    Windows::Foundation::Collections::IObservableVector<hstring> MainWindow::ReplaceMRU()
    {
        return m_replaceMRU;
    }
    
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::PowerRenameUI_new::ExplorerItem> MainWindow::ExplorerItems()
    {
        return m_explorerItems;
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::PowerRenameUI_new::RegExShortcut> MainWindow::SearchRegExShortcuts()
    {
        return m_searchRegExShortcuts;
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::PowerRenameUI_new::RegExShortcut> MainWindow::FileRegExShortcuts()
    {
        return m_fileRegExShortcuts;
    }

    Windows::UI::Xaml::Controls::AutoSuggestBox MainWindow::AutoSuggestBoxSearch()
    {
        return textBox_search();
    }

    Windows::UI::Xaml::Controls::AutoSuggestBox MainWindow::AutoSuggestBoxReplace()
    {
        return textBox_replace();
    }

    Windows::UI::Xaml::Controls::CheckBox MainWindow::ChckBoxRegex()
    {
        return chckBox_regex();
    }

    Windows::UI::Xaml::Controls::CheckBox MainWindow::ChckBoxCaseSensitive()
    {
        return chckBox_case();
    }

    Windows::UI::Xaml::Controls::CheckBox MainWindow::ChckBoxMatchAll()
    {
        return chckBox_matchAll();
    }

    Windows::UI::Xaml::Controls::ComboBox MainWindow::ComboBoxRenameParts()
    {
        return comboBox_renameParts();
    }

    Windows::UI::Xaml::Controls::Primitives::ToggleButton MainWindow::TglBtnIncludeFiles()
    {
        return tglBtn_includeFiles();
    }

    Windows::UI::Xaml::Controls::Primitives::ToggleButton MainWindow::TglBtnIncludeFolders()
    {
        return tglBtn_includeFolders();
    }

    Windows::UI::Xaml::Controls::Primitives::ToggleButton MainWindow::TglBtnIncludeSubfolders()
    {
        return tglBtn_includeSubfolders();
    }

    Windows::UI::Xaml::Controls::Primitives::ToggleButton MainWindow::TglBtnEnumerateItems()
    {
        return tglBtn_enumItems();
    }

    Windows::UI::Xaml::Controls::Primitives::ToggleButton MainWindow::TglBtnUpperCase()
    {
        return tglBtn_upperCase();
    }
    
    Windows::UI::Xaml::Controls::Primitives::ToggleButton MainWindow::TglBtnLowerCase()
    {
        return tglBtn_lowerCase();
    }
    
    Windows::UI::Xaml::Controls::Primitives::ToggleButton MainWindow::TglBtnTitleCase()
    {
        return tglBtn_titleCase();
    }

    Windows::UI::Xaml::Controls::Primitives::ToggleButton MainWindow::TglBtnCapitalize()
    {
        return tglBtn_capitalize();
    }

    Windows::UI::Xaml::Controls::Button MainWindow::BtnRename()
    {
        return btn_rename();
    }

    Windows::UI::Xaml::Controls::Button MainWindow::BtnSettings()
    {
        return btn_settings();
    }

    PowerRenameUI_new::ExplorerItem MainWindow::ChangedItem()
    {
        return m_changedItem;
    }

    void MainWindow::AddExplorerItem(int32_t id, hstring const& original, hstring const& renamed, int32_t type, int32_t parentId, bool checked)
    {
        auto newItem = winrt::make<PowerRenameUI_new::implementation::ExplorerItem>(id, original, renamed, type, checked);
        if (parentId == 0)
        {
            m_explorerItems.Append(newItem);
        }
        else
        {
            auto parent = FindById(parentId);
            parent.Children().Append(newItem);
        }
    }

    void MainWindow::UpdateExplorerItem(int32_t id, hstring const& newName)
    {        
        auto itemToUpdate = FindById(id);
        if (itemToUpdate != NULL)
        {
            itemToUpdate.Renamed(newName);
        }
    }

    void MainWindow::AppendSearchMRU(hstring const& value)
    {
        m_searchMRU.Append(value);
    }

    void MainWindow::AppendReplaceMRU(hstring const& value)
    {
        m_replaceMRU.Append(value);
    }

    PowerRenameUI_new::ExplorerItem MainWindow::FindById(int32_t id)
    {
        auto fakeRoot = winrt::make<PowerRenameUI_new::implementation::ExplorerItem>(0, L"Fake", L"", 0, false);
        fakeRoot.Children(m_explorerItems);
        return FindById(fakeRoot, id);
    }

    PowerRenameUI_new::ExplorerItem MainWindow::FindById(PowerRenameUI_new::ExplorerItem& root, int32_t id)
    {
        if (root.Id() == id)
            return root;

        if (root.Type() == static_cast<UINT>(ExplorerItem::ExplorerItemType::Folder))
        {
            for (auto c : root.Children())
            {
                auto result = FindById(c, id);
                if (result != NULL)
                    return result;
            }
        }

        return NULL;
    }

    void MainWindow::ToggleAll(PowerRenameUI_new::ExplorerItem node, bool checked)
    {
        if (node == NULL)
            return;

        node.Checked(checked);

        if (node.Type() == static_cast<UINT>(ExplorerItem::ExplorerItemType::Folder))
        {
            for (auto c : node.Children())
            {
                ToggleAll(c, checked);
            }
        }
    }
}

void winrt::PowerRenameUI_new::implementation::MainWindow::Checked_ids(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
{
    auto checkbox = sender.as<Windows::UI::Xaml::Controls::CheckBox>();
    // TODO(stefan): Ugly, make it nicer!
    m_changedItem.Original(checkbox.Name());
    m_changedItem.Checked(checkbox.IsChecked().GetBoolean());
}

void winrt::PowerRenameUI_new::implementation::MainWindow::SelectAll(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
{
    auto fakeRoot = winrt::make<PowerRenameUI_new::implementation::ExplorerItem>(0, L"Fake", L"", 0, false);
    fakeRoot.Children(m_explorerItems);
    ToggleAll(fakeRoot, chckBox_selectAll().IsChecked().GetBoolean());
}

void winrt::PowerRenameUI_new::implementation::MainWindow::btn_showAll_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
{
    btn_showAll().IsChecked(true);
    btn_showRenamed().IsChecked(false);
    if (m_changedItem.Type() != 0)
    {
        m_explorerItems.Clear();
        m_changedItem.Type(0);    
    }
}

void winrt::PowerRenameUI_new::implementation::MainWindow::btn_showRenamed_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
{
    btn_showRenamed().IsChecked(true);
    btn_showAll().IsChecked(false);
    if (m_changedItem.Type() != 1)
    {
        m_explorerItems.Clear();
        m_changedItem.Type(1);
    }
}

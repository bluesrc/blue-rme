//////////////////////////////////////////////////////////////////////
// This file is part of Remere's Map Editor
//////////////////////////////////////////////////////////////////////
// Remere's Map Editor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Remere's Map Editor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include "main.h"

#include "result_window.h"
#include "gui.h"
#include "position.h"

BEGIN_EVENT_TABLE(SearchResultWindow, wxPanel)
	EVT_LISTBOX(wxID_ANY, SearchResultWindow::OnClickResult)
	EVT_BUTTON(wxID_FILE, SearchResultWindow::OnClickExport)
	EVT_BUTTON(wxID_CLEAR, SearchResultWindow::OnClickClear)
END_EVENT_TABLE()

SearchResultWindow::SearchResultWindow(wxWindow* parent) :
	wxPanel(parent, wxID_ANY)
{
	wxSizer* sizer = newd wxBoxSizer(wxVERTICAL);
	result_list = newd wxListBox(this, wxID_ANY, wxDefaultPosition, wxSize(200, 330), 0, nullptr, wxLB_SINGLE | wxLB_ALWAYS_SB);
	sizer->Add(result_list, wxSizerFlags(1).Expand());

	wxSizer* buttonsSizer = newd wxBoxSizer(wxHORIZONTAL);
	buttonsSizer->Add(newd wxButton(this, wxID_FILE, "Export"), wxSizerFlags(0).Center());
	buttonsSizer->Add(newd wxButton(this, wxID_CLEAR, "Clear"), wxSizerFlags(0).Center());
	sizer->Add(buttonsSizer, wxSizerFlags(0).Center().DoubleBorder());
	SetSizerAndFit(sizer);
}

SearchResultWindow::~SearchResultWindow()
{
	Clear();
}

void SearchResultWindow::Clear()
{
	for(uint32_t n = 0; n < result_list->GetCount(); ++n) {
		delete reinterpret_cast<Position*>(result_list->GetClientData(n));
	}
	result_list->Clear();
}

void SearchResultWindow::AddPosition(wxString description, Position pos)
{
	result_list->Append(description << " (" << pos.x << "," << pos.y << "," << pos.z << ")", newd Position(pos));
}

void SearchResultWindow::OnClickResult(wxCommandEvent& event)
{
	Position* pos = reinterpret_cast<Position*>(event.GetClientData());
	if(pos) {
		g_gui.SetScreenCenterPosition(*pos);
	}
}

void SearchResultWindow::OnClickExport(wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog dialog(this, "Save file...", "", "", "Text Documents (*.txt) | *.txt", wxFD_SAVE);
	if(dialog.ShowModal() == wxID_OK) {
		wxFile file(dialog.GetPath(), wxFile::write);
		if(file.IsOpened()) {
			g_gui.CreateLoadBar("Exporting search result...");

			file.Write("Generated by Remere's Map Editor " + __BLUERME_VERSION__);
			file.Write("\n=============================================\n\n");
			wxArrayString lines = result_list->GetStrings();
			size_t count = lines.Count();
			for(size_t i = 0; i < count; ++i) {
				file.Write(lines[i] + "\n");
				g_gui.SetLoadScale((int32_t)i, (int32_t)count);
			}
			file.Close();

			g_gui.DestroyLoadBar();
		}
	}
}

void SearchResultWindow::OnClickClear(wxCommandEvent& WXUNUSED(event))
{
	Clear();
}

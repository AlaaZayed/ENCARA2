/////////////////////////////////////////////////////////////////////////////
// 
// Adaptado por Modesto Castrill�n Santana para usar OpenCV
// 19/11/08
// Licence:     wxWindows licence
//
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// Declaraciones
// ============================================================================

// ----------------------------------------------------------------------------
// Cabeceras
// ----------------------------------------------------------------------------


// For compilers that support precompilation, includes "wx/wx.h".
//#include "wx/wxprec.h"

//Sobre el error de ole ver http://article.gmane.org/gmane.comp.lib.opencv/24516

 
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif


#include "Interface.h"


// Creaci�n de un objeto de aplicaci�n
IMPLEMENT_APP(MainApp)

// ============================================================================
// Implementaci�n
// ============================================================================

// ----------------------------------------------------------------------------
// Clase de aplicaci�n
// ----------------------------------------------------------------------------

// Programa principal
bool MainApp::OnInit()
{
    // Llamada al m�todo de inicialicaci�n que puede realizar distintas acciones
	// aunque en este ejemplo sea sencillo
    if ( !wxApp::OnInit() )
        return false;

    // Creaci�n de la ventana principal de la aplicaci�n
    MainFrame *frame = new MainFrame(_T("Aplicaci�n wxWidgets"));

    // Muestra la ventana
    frame->Show(true);

    // Tras esta acci�n, fuera correcto se entra en el en un bucle infinito a la espera
	// de acciones de la interfaz. Si se retorna false la aplicaci�n finaliza.
    return true;
}

// ----------------------------------------------------------------------------
// Ventana principal
// ----------------------------------------------------------------------------

// Cosntructor
MainFrame::MainFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{

#if wxUSE_MENUS
    // Crea los elementos de la barra de men�

	//Men� de ficheros
    wxMenu *subMenu1 = new wxMenu;
	subMenu1->Append(Submenu1_Ficheros, _T("&Abre Fichero\tAlt-F"));
	subMenu1->AppendSeparator();
    subMenu1->Append(Submenu1_Quit, _T("&Salir\tAlt-S"), _T("Salir"));

	//Men� de proceso
    wxMenu *subMenu2 = new wxMenu;
	subMenu2->Append(Submenu2_StartCam, _T("&Activa c�mara ....\tAlt-A"));
	subMenu2->Append(Submenu2_StopCam, _T("&Para c�mara ....\tAlt-P"));
	
    // Elemento "About" estar� en el men� de ayuda
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(About, _T("&Acerca de...\tF1"), _T("Muestra di�logo About"));

    // Asociamos el men� a la barra de men�
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(subMenu1, _T("&Ficheros"));
	menuBar->Append(subMenu2, _T("&Procesa"));
    menuBar->Append(helpMenu, _T("&Ayuda"));

    // ... enganchamos la barra de men� a la ventana
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // Creamos una barra de estado
    CreateStatusBar(2);
    SetStatusText(_T("�Bienvenido a wxWidgets!"));
#endif // wxUSE_STATUSBAR


	//Initializations
	m_boCapturando=m_boImagenCargada=false;


	//ENCARA2
	FILE *fdata=fopen("ENCARAdataconfig.txt","r");

	//If the config file exists, the path it taken from that file
	if (fdata!=NULL)
	{
		char auxchar[200];
		bool boprimera=true;
		strcpy(ENCARAdataDir,"");

		//Carga la ruta de forma reiterativa si hubiera espacios intermedios
		while (fscanf(fdata,"%s",auxchar)!=EOF)
		{
			if (!boprimera) strcat(ENCARAdataDir," ");//Est� partida por un espacio a partir de la segunda
			strcat(ENCARAdataDir,auxchar);
			boprimera=false;
		}
		fscanf(fdata,"%s",ENCARAdataDir);
		fclose(fdata);
	}
	else
	{
		//Gets the environment variable
		char *ENCARA2=getenv("ENCARA2");

		if (ENCARA2==NULL)
		{
			//ENCARA2.2 data directory (to be modified according to your configuration)
			sprintf(ENCARAdataDir,"D:\\Modesto\\FACES\\ENCARA2data");
		}
		else
		{
			//ENCARA2.2 data directory using the environment variable
			sprintf(ENCARAdataDir,"%s\\ENCARA2data",ENCARA2);
		}
	}

	//Defaults dimensions
	m_width=320;
	m_height=240;

	//ENCARA2 creation
	ENCARAFaceDetector=new CENCARA2_2Detector(ENCARAdataDir,m_width,m_height);


}


// Manejadores de eventos

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	if (m_boCapturando)
	{		
		cvReleaseCapture(&m_capture);
		cvDestroyWindow("Camera");
	}

	if (m_boImagenCargada)
		cvDestroyWindow("Image");

	//ENCARA2
	delete ENCARAFaceDetector;
	
    // true is to force the frame to close
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxString::Format(
                    _T("�Bienvenido a %s!\n")
                    _T("\n")
                    _T("Ejemplo wxWidgets \n")
                    _T("bajo %s."),
                    wxVERSION_STRING,
                    wxGetOsDescription().c_str()
                 ),
                 _T("Ejemplo wxWidgets"),
                 wxOK | wxICON_INFORMATION,
                 this);
}

void MainFrame::MiLlamada(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxString::Format(
                    _T("�Bien pulsado!\n")
                 ),
                 _T("Pulsado"),
                 wxOK | wxICON_INFORMATION,
                 this);
}

void MainFrame::StartCam(wxCommandEvent& WXUNUSED(event))
{
    //Close still open channels
	if (m_boCapturando)
	{		
		cvReleaseCapture(&m_capture);
	}

	m_boCapturando=true;

	m_capture=cvCreateCameraCapture(0);//Since ver 1.1 using -1 crashes

	cvNamedWindow("Camera", 1);

	while (m_boCapturando)
	{
		IplImage *h=cvQueryFrame(m_capture);

		if (h)
		{

			//Process the image
			//The last parameter indicates that recognition 
			ENCARAFaceDetector->ApplyENCARA2(h,2);

			//Paints results
			ENCARAFaceDetector->PaintFacialData(h,CV_RGB(0,255,0));
		

			cvShowImage("Camera",h);
		}

		cvWaitKey(10);
	}

	cvDestroyWindow("Camera");
}

void MainFrame::StopCam(wxCommandEvent& WXUNUSED(event))
{
    //Close open channels
	if (m_boCapturando)
	{		
		cvReleaseCapture(&m_capture);
		cvDestroyWindow("Camera");
	}
	m_boCapturando=false;
}

void MainFrame::FileDialog(wxCommandEvent& WXUNUSED(event))
{
	// The Path to the file we have open
	wxString CurrentDocPath;

    wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Choose a file to open"), wxEmptyString, wxEmptyString, 
		_("Image files (*.png, *.jpg)|*.png;*.jpg"),

		wxFD_OPEN, wxDefaultPosition);

	
	// Creates a "open file" dialog with 4 file types
	if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
		CurrentDocPath = OpenDialog->GetPath();

		//Cargamos y mostramos la imagen le�da
		IplImage *h = cvLoadImage(CurrentDocPath);

		cvNamedWindow("Image", 1);
		//cvMoveWindow("Image",0,0);
		cvShowImage("Image",h);

		m_boImagenCargada=true;

		cvReleaseImage(&h);

	}

}




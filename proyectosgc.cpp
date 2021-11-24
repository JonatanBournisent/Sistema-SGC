//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("fReportes.cpp", Reportes);
USEFORM("uEliminarComprobante.cpp", EliminarComprobante);
USEFORM("sgc.cpp", Form1);
USEFORM("fOpciones.cpp", Opciones);
USEFORM("fAsociaciones.cpp", Asociaciones);
USEFORM("fAgregarContribuyente.cpp", AgregarContribuyente);
USEFORM("fCargarCompras.cpp", CargarCompras);
USEFORM("fModificarCuentas.cpp", ModificarCuentas);
USEFORM("fCargarVentas.cpp", CargarVentas);
USEFORM("uMostrarComprobantes.cpp", fMostrarComprobantes);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TCargarCompras), &CargarCompras);
		Application->CreateForm(__classid(TAgregarContribuyente), &AgregarContribuyente);
		Application->CreateForm(__classid(TOpciones), &Opciones);
		Application->CreateForm(__classid(TCargarVentas), &CargarVentas);
		Application->CreateForm(__classid(TAsociaciones), &Asociaciones);
		Application->CreateForm(__classid(TReportes), &Reportes);
		Application->CreateForm(__classid(TEliminarComprobante), &EliminarComprobante);
		Application->CreateForm(__classid(TModificarCuentas), &ModificarCuentas);
		Application->CreateForm(__classid(TfMostrarComprobantes), &fMostrarComprobantes);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------

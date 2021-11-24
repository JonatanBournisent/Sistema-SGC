//---------------------------------------------------------------------------

#include <vcl.h>
#include <dateUtils.hpp>
#pragma hdrstop

#include "sgc.h"
#include "fCargarCompras.h"
#include "fCargarVentas.h"
#include "fOpciones.h"
#include "fReportes.h"
#include "fAsociaciones.h"
#include "fAgregarContribuyente.h"
#include "uEliminarComprobante.h"
#include "fModificarCuentas.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
   AgregarContribuyente->llamador = 1;
   AgregarContribuyente->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
   CargarVentas->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
   Asociaciones->llamador = 1;
   Asociaciones->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
   CargarCompras->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
   Reportes->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
   EliminarComprobante->ShowModal();
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Button5Click(TObject *Sender)
{
   ModificarCuentas->ShowModal();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormShow(TObject *Sender)
{
   Form1->SetFocus();
}
//---------------------------------------------------------------------------



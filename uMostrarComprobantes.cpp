//---------------------------------------------------------------------------

#include <vcl.h>
#include <dateUtils.hpp>
#pragma hdrstop

#include "uMostrarComprobantes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfMostrarComprobantes *fMostrarComprobantes;
//---------------------------------------------------------------------------
__fastcall TfMostrarComprobantes::TfMostrarComprobantes(TComponent* Owner)
	: TForm(Owner)
{
}




//---------------------------------------------------------------------------


void TfMostrarComprobantes::VerificarDatos(TObject *Sender)
{
   if(dynamic_cast <TEdit *>(Sender) != NULL)
   {
	  TEdit *Edit = dynamic_cast <TEdit *>(Sender);

      if(Sender == EdPeriodo)
	  {
		  if(Edit->Text != "__/____")
		  {
			 if(Edit->Text.Pos("_") > 0)
			 {
				 Edit->Color = clWebLightCoral;
				 Edit->Hint = "No se completó el período";
				 Edit->ShowHint = true;
				 perOK = false;
			 }
			 else if(!IsValidDate(StrToInt(Edit->Text.SubString(4,4)), StrToInt(Edit->Text.SubString(1,2)), 1))
			 {
				 Edit->Color = clWebLightCoral;
				 Edit->Hint = "El período ingresado no representa una fecha válida";
				 Edit->ShowHint = true;
				 perOK = false;
			 }
			 else
			 {
				Edit->Color = clWindow;
				Edit->ShowHint = false;
				perOK = true;
			 }
		 }
		 else
		 {
			Edit->Color = clWebLightCoral;
			Edit->Hint = "No se completó el período";
			Edit->ShowHint = true;
			perOK = false;
		 }
	  }
   }
}

//---------------------------------------------------------------------------
void __fastcall TfMostrarComprobantes::FormShow(TObject *Sender)
{
   fMostrarComprobantes->Height = 591;

   Button1->Left = fMostrarComprobantes->Width / 6;
   Button2->Left = (fMostrarComprobantes->Width / 6) * 5 - Button2->Width;
   Button3->Left = (Button2->Left - (Button1->Left + Button1->Width)) / 2 + Button1->Left + Button1->Width - (Button3->Width / 2);
   EdPeriodo->Text = "__/____";
   modificando = false;
   Button3->Caption = "Modificar período";

   retorno = 0;

   Query1->Close();
   CDS->Active = false;

   if(llamador == 0)
   {
	  DBG1->Columns->Items[1]->Title->Caption = "Cliente";
	  DBG1->Columns->Items[1]->FieldName = "cliente";
	  DBG1->Columns->Items[6]->FieldName = "desCuentaVenta";
	  CDSdesCuentaCompra->FieldName = "desCuentaVenta";
	  CDSidComprobanteCompra->FieldName = "idComprobanteVenta";
	  CDSproveedor->FieldName = "cliente";
   }
   else if(llamador == 1)
   {
	  DBG1->Columns->Items[1]->Title->Caption = "Proveedor";
	  DBG1->Columns->Items[1]->FieldName = "proveedor";
	  DBG1->Columns->Items[6]->FieldName = "desCuentaCompra";
	  CDSdesCuentaCompra->FieldName = "desCuentaCompra";
	  CDSidComprobanteCompra->FieldName = "idComprobanteCompra";
	  CDSproveedor->FieldName = "proveedor";
   }

   AnsiString q;

   q = "SELECT fechaComprobante, ptoVenta, nroComprobante, idTipo, idDocumento, ";

   if(llamador == 0)
	  q = q + "idComprobanteVenta, ";
   else if(llamador == 1)
	  q = q + "idComprobanteCompra, ";

   q = q + "(SELECT razonSocial FROM contribuyentes WHERE refContribuyente = idContribuyente) AS contribuyente, ";
   if(llamador == 0)
   {
	  q = q + "(SELECT razonSocial FROM contribuyentes WHERE refCliente = idContribuyente) AS cliente, ";
      q = q + "(SELECT cuit FROM contribuyentes WHERE refCliente = idContribuyente) AS cuit, ";
	  q = q + "desTipo, desDocumento, desCuentaVenta, ";
   }
   if(llamador == 1)
   {
	  q = q + "(SELECT razonSocial FROM contribuyentes WHERE refProveedor = idContribuyente) AS proveedor, ";
	  q = q + "(SELECT cuit FROM contribuyentes WHERE refProveedor = idContribuyente) AS cuit, ";
	  q = q + "desTipo, desDocumento, desCuentaCompra, ";
   }

   q = q + "netoGravado1, netoGravado2, netoGravado3, netoGravado4,";
   q = q + "(netoGravado1 * 0.21 + netoGravado2 * 0.105 + netoGravado3 * 0.27) AS totIVA, ";
   q = q + "retencionesIVA, percepcionesIVA, retencionesIB, percepcionesIB, retencionesGanancias, ";
   q = q + "conceptosNoGravados, exentos, total, desJurisdiccion ";
   if(llamador == 0)
   {
	  q = q + "FROM comprobantesVentas ";
	  q = q + "INNER JOIN tipos ON comprobantesVentas.refTipo = tipos.idTipo ";
	  q = q + "INNER JOIN documentos ON comprobantesVentas.refDocumento = documentos.idDocumento ";
	  q = q + "INNER JOIN cuentasVentas ON comprobantesVentas.refCuentaVenta = cuentasVentas.idCuentaVenta ";
	  q = q + "INNER JOIN jurisdicciones ON comprobantesVentas.refJurisdiccion = jurisdicciones.idJurisdiccion ";
   }
   else if(llamador == 1)
   {
	  q = q + "FROM comprobantesCompras ";
	  q = q + "INNER JOIN tipos ON comprobantesCompras.refTipo = tipos.idTipo ";
	  q = q + "INNER JOIN documentos ON comprobantesCompras.refDocumento = documentos.idDocumento ";
	  q = q + "INNER JOIN cuentasCompras ON comprobantesCompras.refCuentaCompra = cuentasCompras.idCuentaCompra ";
	  q = q + "INNER JOIN jurisdicciones ON comprobantesCompras.refJurisdiccion = jurisdicciones.idJurisdiccion ";
   }

   q = q + "WHERE refContribuyente = :v1 AND fechaPeriodo = :v2 ";


   if(llamador == 0)
	  q = q + "ORDER BY ptoVenta, nroComprobante ASC ";
   else if(llamador == 1)
	  q = q + "ORDER BY fechaComprobante ASC ";


   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add(q);
   Query1->ParamByName("v1")->AsInteger = idContribuyente;
   Query1->ParamByName("v2")->AsDate = StrToDate("01/" + periodo);
   Query1->Open();


   CDS->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall TfMostrarComprobantes::FormClose(TObject *Sender, TCloseAction &Action)

{
   CDS->Active = false;
   Query1->Close();
   Close();
}
//---------------------------------------------------------------------------


void __fastcall TfMostrarComprobantes::Button1Click(TObject *Sender)
{
   if(llamador == 0)
	  retorno = CDS->FieldByName("idComprobanteVenta")->AsInteger;
   else if(llamador == 1)
	  retorno = CDS->FieldByName("idComprobanteCompra")->AsInteger;

   Close();
}
//---------------------------------------------------------------------------


void __fastcall TfMostrarComprobantes::Button2Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------


void __fastcall TfMostrarComprobantes::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(Key == VK_ESCAPE || Key == VK_RETURN)
	  fMostrarComprobantes->Close();
}
//---------------------------------------------------------------------------



void __fastcall TfMostrarComprobantes::Modificarfecha1Click(TObject *Sender)
{
   if(llamador == 0)
	  ShowMessage(IntToStr(CDS->FieldByName("idComprobanteVenta")->AsInteger));
   else if(llamador == 1)
	  ShowMessage(IntToStr(CDS->FieldByName("idComprobanteCompra")->AsInteger));
}
//---------------------------------------------------------------------------

void __fastcall TfMostrarComprobantes::EdPeriodoKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
   if(Key == VK_BACK)
   {
	  Key = NULL;
	  EdPeriodo->Text = "___/____";
	  EdPeriodo->SelStart = 0;
   }
   else if(Key == VK_DELETE)
   {
	  Key = NULL;
	  EdPeriodo->Text = "__/____";
	  EdPeriodo->SelStart = 0;
   }
}
//---------------------------------------------------------------------------

void __fastcall TfMostrarComprobantes::EdPeriodoKeyPress(TObject *Sender, System::WideChar &Key)

{
   EdPeriodo->SelLength = 1;
}
//---------------------------------------------------------------------------

void __fastcall TfMostrarComprobantes::EdPeriodoKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
   if(EdPeriodo->SelStart == 2)
	  EdPeriodo->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TfMostrarComprobantes::EdPeriodoMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   if(EdPeriodo->SelStart == 2)
	  EdPeriodo->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TfMostrarComprobantes::EdPeriodoExit(TObject *Sender)
{
   VerificarDatos(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TfMostrarComprobantes::DBG1DblClick(TObject *Sender)
{
   if(!modificando)
	  return;

   if(!perOK)
   {
	  Application->MessageBox(L"El período ingresado no es válido",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  return;
   }
   if(EndOfTheMonth(StrToDate("01/" + EdPeriodo->Text)) < StrToDate(CDS->FieldByName("fechaComprobante")->AsString))
   {
	  Application->MessageBox(L"El período ingresado es inferior a la fecha del comprobante",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  return;
   }


   int id;

   if(llamador == 0)
	  id = CDS->FieldByName("idComprobanteVenta")->AsInteger;
   else if(llamador == 1)
	  id = CDS->FieldByName("idComprobanteCompra")->AsInteger;

   AnsiString per = L"El nuevo período será: " + EdPeriodo->Text + L". Desea continuar?";

   wchar_t *str = new wchar_t[per.WideCharBufSize()];
   per.WideChar(str, per.WideCharBufSize());


   if(Application->MessageBox(str ,L"Se va a modificar el período!", MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES)
   {
	  AuxQuery->Close();
	  AuxQuery->SQL->Clear();
	  if(llamador == 0)
		 AuxQuery->SQL->Add("UPDATE comprobantesVentas SET fechaPeriodo = :p WHERE (idComprobanteVenta = :id)");
	  else if(llamador == 1)
		 AuxQuery->SQL->Add("UPDATE comprobantesCompras SET fechaPeriodo = :p WHERE (idComprobanteCompra = :id)");

	  AuxQuery->ParamByName("p")->AsDate = StrToDate("01/" + EdPeriodo->Text);
	  AuxQuery->ParamByName("id")->AsInteger = id;
	  AuxQuery->ExecSQL();

	  CDS->Refresh();

   }

   delete str;
}
//---------------------------------------------------------------------------

void __fastcall TfMostrarComprobantes::Button3Click(TObject *Sender)
{
   fMostrarComprobantes->Height = 710;
   Button3->Caption = "*Modificando";
   modificando = true;
}
//---------------------------------------------------------------------------


void __fastcall TfMostrarComprobantes::Button4Click(TObject *Sender)
{
   fMostrarComprobantes->Height = 591;
   EdPeriodo->Text = "__/____";
   modificando = false;
   Button3->Caption = "Modificar período";
}
//---------------------------------------------------------------------------


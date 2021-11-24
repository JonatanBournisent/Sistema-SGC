//---------------------------------------------------------------------------

#include <vcl.h>
#include <dateUtils.hpp>
#include <FileCtrl.hpp>
#include <System.hpp>

#pragma hdrstop

#include "fReportes.h"
#include "fOpciones.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const xlHAlignCenter = -4108;


TReportes *Reportes;
//---------------------------------------------------------------------------
__fastcall TReportes::TReportes(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TReportes::VerificarDatos(TObject *Sender)
{
   if(dynamic_cast <TEdit *>(Sender) != NULL)
   {
	  TEdit *Edit = dynamic_cast <TEdit *>(Sender);

	  if(Sender == EdContribuyente)
	  {
		  if(Edit->Text != "__-________-_")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT idContribuyente, razonSocial FROM Contribuyentes WHERE(cuit = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				desContribuyente->Caption = AuxQuery->FieldByName("razonSocial")->AsString;
				idContribuyente = AuxQuery->FieldByName("idContribuyente")->AsInteger;
				Edit1->Text = IntToStr(idContribuyente);
				Edit->Color = clWindow;
				conOK = true;
			 }
			 else
			 {
				desContribuyente->Caption = "Contribuyente desconocido";
				idContribuyente = 0;
				Edit1->Text = "";
				Edit->Color = clWebLightCoral;
				conOK = false;
			 }
		  }
		  else
		  {
			 desContribuyente->Caption = "";
			 Edit->Color = clWebLightCoral;
			 idContribuyente = 0;
			 Edit1->Text = "";
			 conOK = false;
		  }
		  AuxQuery->Close();

		/*  if(conOK && perOK)
		  {
			 RG1->Enabled = true;
		  }
		  else
		  {
			 RG1->Enabled = false;
		  }
         */
		  CB1->Clear();
		  CB1->Enabled = false;
		  CB2->Clear();
		  CB2->Enabled = false;
		  EdProCli->Enabled = false;
	  }
	  if(Sender == EdProCli)
	  {
		  if(Edit->Text != "__-________-_")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT idContribuyente, razonSocial FROM Contribuyentes WHERE(cuit = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				desProCli->Caption = AuxQuery->FieldByName("razonSocial")->AsString;
				idProCli = AuxQuery->FieldByName("idContribuyente")->AsInteger;
                Edit2->Text = IntToStr(idProCli);
				Edit->Color = clWindow;
				procliOK = true;
			 }
			 else
			 {
				desProCli->Caption = "Contribuyente desconocido";
				idProCli = 0;
				Edit2->Text = "";
				Edit->Color = clWebLightCoral;
				procliOK = false;
			 }
		  }
		  else
		  {
			 desProCli->Caption = "Todos";
			 Edit->Color = clGradientActiveCaption;
			 idProCli = 0;
			 Edit2->Text = "";
			 procliOK = false;
		  }
		  AuxQuery->Close();
	  }
	  else if(Sender == EdPeriodo)
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
		 /*
		  if(conOK && perOK)
		  {
			 RG1->Enabled = true;
		  }
		  else
		  {
			 RG1->Enabled = false;
		  }
		  */
		  CB1->Clear();
		  CB1->Enabled = false;
		  CB2->Clear();
		  CB2->Enabled = false;
		  EdProCli->Enabled = false;
	  }
   }
   else
	  ShowMessage("ERROR: El *Sender no es una clase TEdit");
}
//---------------------------------------------------------------------------

void TReportes::Buscar(void)
{
   AnsiString q;

   int idCuenta;
   int idJurisdiccion;

   if(RG1->ItemIndex == 0)
   {
	  AuxQuery->SQL->Clear();
	  AuxQuery->SQL->Add("SELECT idCuentaVenta FROM cuentasventas WHERE desCuentaVenta = :v");
	  AuxQuery->ParamByName("v")->AsString = CB2->Items->Strings[CB2->ItemIndex];
	  AuxQuery->Open();
	  idCuenta = AuxQuery->FieldByName("idCuentaVenta")->AsInteger;
   }
   if(RG1->ItemIndex == 1)
   {
	  AuxQuery->SQL->Clear();
	  AuxQuery->SQL->Add("SELECT idCuentaCompra FROM cuentascompras WHERE desCuentaCompra = :v");
	  AuxQuery->ParamByName("v")->AsString = CB2->Items->Strings[CB2->ItemIndex];
	  AuxQuery->Open();
	  idCuenta = AuxQuery->FieldByName("idCuentaCompra")->AsInteger;
   }
   AuxQuery->Close();


   q = "SELECT fechaComprobante, ptoVenta, nroComprobante, idTipo, idDocumento, ";
   q = q + "(SELECT razonSocial FROM contribuyentes WHERE refContribuyente = idContribuyente) AS contribuyente, ";
   if(RG1->ItemIndex == 0)
   {
	  q = q + "(SELECT razonSocial FROM contribuyentes WHERE refCliente = idContribuyente) AS cliente, ";
      q = q + "(SELECT cuit FROM contribuyentes WHERE refCliente = idContribuyente) AS cuit, ";
	  q = q + "desTipo, desDocumento, desCuentaVenta, ";
   }
   if(RG1->ItemIndex == 1)
   {
	  q = q + "(SELECT razonSocial FROM contribuyentes WHERE refProveedor = idContribuyente) AS proveedor, ";
      q = q + "(SELECT cuit FROM contribuyentes WHERE refProveedor = idContribuyente) AS cuit, ";
	  q = q + "desTipo, desDocumento, desCuentaCompra, ";
   }

   q = q + "netoGravado1, netoGravado2, netoGravado3, netoGravado4, ";
   q = q + "(netoGravado1 * 0.21 + netoGravado2 * 0.105 + netoGravado3 * 0.27) AS totIVA, ";
   q = q + "retencionesIVA, percepcionesIVA, retencionesIB, percepcionesIB, retencionesGanancias, ";
   q = q + "conceptosNoGravados, exentos, total, desJurisdiccion ";
   if(RG1->ItemIndex == 0)
   {
	  q = q + "FROM comprobantesVentas ";
	  q = q + "INNER JOIN tipos ON comprobantesVentas.refTipo = tipos.idTipo ";
	  q = q + "INNER JOIN documentos ON comprobantesVentas.refDocumento = documentos.idDocumento ";
	  q = q + "INNER JOIN cuentasVentas ON comprobantesVentas.refCuentaVenta = cuentasVentas.idCuentaVenta ";
	  q = q + "INNER JOIN jurisdicciones ON comprobantesVentas.refJurisdiccion = jurisdicciones.idJurisdiccion ";
   }
   else if(RG1->ItemIndex == 1)
   {
	  q = q + "FROM comprobantesCompras ";
	  q = q + "INNER JOIN tipos ON comprobantesCompras.refTipo = tipos.idTipo ";
	  q = q + "INNER JOIN documentos ON comprobantesCompras.refDocumento = documentos.idDocumento ";
	  q = q + "INNER JOIN cuentasCompras ON comprobantesCompras.refCuentaCompra = cuentasCompras.idCuentaCompra ";
	  q = q + "INNER JOIN jurisdicciones ON comprobantesCompras.refJurisdiccion = jurisdicciones.idJurisdiccion ";
   }
   if(CB1->ItemIndex <= 0)
	  q = q + "WHERE refContribuyente = :v1 AND fechaPeriodo = :v2 ";
   else
   {
	  AuxQuery->Close();
	  AuxQuery->SQL->Clear();
	  AuxQuery->SQL->Add("SELECT idJurisdiccion FROM jurisdicciones WHERE desJurisdiccion = :v");
	  AuxQuery->ParamByName("v")->AsString = CB1->Items->Strings[CB1->ItemIndex];
	  AuxQuery->Open();
	  idJurisdiccion = AuxQuery->FieldByName("idJurisdiccion")->AsInteger;
	  AuxQuery->Close();

	  q = q + "WHERE refContribuyente = :v1 AND fechaPeriodo = :v2 AND refJurisdiccion = :v3 ";
   }

   if(RG1->ItemIndex == 0)
   {
	  if(CB2->ItemIndex > 0)
		 q = q + "AND refCuentaVenta = :v4 ";
   }
   else if(RG1->ItemIndex == 1)
   {
	  if(CB2->ItemIndex > 0)
		 q = q + "AND refCuentaCompra = :v4 ";
   }

   if(idProCli > 0)
   {
	  if(RG1->ItemIndex == 0)
	  {
		 q = q + "AND refCliente = :v5 ";
	  }
	  else if(RG1->ItemIndex == 1)
	  {
		 q = q + "AND refProveedor = :v5 ";
      }
   }

   if(CkB1->Checked)
	  q = q + "AND RetencionesIVA > 0 ";
   if(CkB2->Checked)
	  q = q + "AND PercepcionesIVA > 0 ";
   if(CkB3->Checked)
	  q = q + "AND RetencionesIB > 0 ";
   if(CkB4->Checked)
	  q = q + "AND PercepcionesIB > 0 ";
   if(CkB5->Checked)
	  q = q + "AND RetencionesGanancias > 0 ";

   if(RG1->ItemIndex == 0)
	  q = q + "ORDER BY PtoVenta, NroComprobante ASC ";     //En las ventas es mejor que esten ordenados por numero
   else if(RG1->ItemIndex == 1)
	  q = q + "ORDER BY fechaComprobante ASC ";


   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add(q);
   Query1->ParamByName("v1")->AsInteger = idContribuyente;
   Query1->ParamByName("v2")->AsDate = StrToDate("01/" + EdPeriodo->Text);
   if(CB1->ItemIndex > 0)
	  Query1->ParamByName("v3")->AsInteger = idJurisdiccion;
   if(CB2->ItemIndex > 0)
	  Query1->ParamByName("v4")->AsInteger = idCuenta;
   if(idProCli > 0)
      Query1->ParamByName("v5")->AsInteger = idProCli;
   Query1->Open();


   CDS->Active = false;
   CDS->Active = true;

  // TFloatField(CDS->FieldByName("netoGravado1")).DisplayFormat = "$ 0.00";


   q = "SELECT SUM(netoGravado1) AS s1, SUM(netoGravado2) AS s2, SUM(netoGravado3) AS s3, SUM(netoGravado4) AS s4, ";
   q = q + "SUM(retencionesIVA) AS riva, SUM(percepcionesIVA) AS piva, ";
   q = q + "SUM(retencionesIB) AS rib, SUM(percepcionesIB) AS pib, ";
   q = q + "SUM(retencionesGanancias) AS rga, SUM(conceptosNoGravados) AS cng, ";
   q = q + "SUM(exentos) AS exe, SUM(total) AS tot ";

   if(RG1->ItemIndex == 0)
   {
	   q = q + "FROM comprobantesVentas ";
   }
   else if(RG1->ItemIndex == 1)
   {
	  q = q + "FROM comprobantesCompras ";
   }

   if(CB1->ItemIndex <= 0)
	  q = q + "WHERE refContribuyente = :v1 AND fechaPeriodo = :v2 ";
   else
	  q = q + "WHERE refContribuyente = :v1 AND fechaPeriodo = :v2 AND refJurisdiccion = :v3 ";

   if(RG1->ItemIndex == 0)
   {
	  if(CB2->ItemIndex > 0)
		 q = q + "AND refCuentaVenta = :v4 ";
   }
   else if(RG1->ItemIndex == 1)
   {
	  if(CB2->ItemIndex > 0)
		 q = q + "AND refCuentaCompra = :v4 ";
   }

   if(idProCli > 0)
   {
	  if(RG1->ItemIndex == 0)
	  {
		 q = q + "AND refCliente = :v5 ";
	  }
	  else if(RG1->ItemIndex == 1)
	  {
		 q = q + "AND refProveedor = :v5 ";
      }
   }

   if(CkB1->Checked)
	  q = q + "AND RetencionesIVA > 0 ";
   if(CkB2->Checked)
	  q = q + "AND PercepcionesIVA > 0 ";
   if(CkB3->Checked)
	  q = q + "AND RetencionesIB > 0 ";
   if(CkB4->Checked)
	  q = q + "AND PercepcionesIB > 0 ";
   if(CkB5->Checked)
	  q = q + "AND RetencionesGanancias > 0 ";


   AuxQuery->Close();
   AuxQuery->SQL->Clear();
   AuxQuery->SQL->Add(q);
   AuxQuery->ParamByName("v1")->AsInteger = idContribuyente;
   AuxQuery->ParamByName("v2")->AsDate = StrToDate("01/" + EdPeriodo->Text);
   if(CB1->ItemIndex > 0)
	  AuxQuery->ParamByName("v3")->AsInteger = idJurisdiccion;
   if(CB2->ItemIndex > 0)
	  AuxQuery->ParamByName("v4")->AsInteger = idCuenta;
   if(idProCli > 0)
      AuxQuery->ParamByName("v5")->AsInteger = idProCli;
   AuxQuery->Open();

   AuxQuery->ParamByName("v1")->AsInteger = idContribuyente;
   Label14->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("s1")->AsFloat);
   Label15->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("s2")->AsFloat);
   Label16->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("s3")->AsFloat);
   Label17->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("s4")->AsFloat);
   Label18->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("riva")->AsFloat);
   Label19->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("piva")->AsFloat);
   Label20->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("rib")->AsFloat);
   Label21->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("pib")->AsFloat);
   Label22->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("rga")->AsFloat);
   Label23->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("cng")->AsFloat);
   Label24->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("exe")->AsFloat);
   Label25->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("tot")->AsFloat);
   Label26->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("s1")->AsFloat * 0.21);
   Label27->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("s2")->AsFloat * 0.105);
   Label28->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("s3")->AsFloat * 0.27);
   Label29->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("s4")->AsFloat * 0.00);
   Label37->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("s1")->AsFloat * 0.21 + AuxQuery->FieldByName("s2")->AsFloat * 0.105 + AuxQuery->FieldByName("s3")->AsFloat * 0.27);

   AuxQuery->Close();

//******************************************************
// esto es para sumar los comprobantes C y que el total sea correcto

   q = "SELECT SUM(total) AS totC ";

   if(RG1->ItemIndex == 0)
   {
	   q = q + "FROM comprobantesVentas ";
   }
   else if(RG1->ItemIndex == 1)
   {
	  q = q + "FROM comprobantesCompras ";
   }

   if(CB1->ItemIndex <= 0)
	  q = q + "WHERE refContribuyente = :v1 AND fechaPeriodo = :v2 AND refTipo = 3 ";
   else
	  q = q + "WHERE refContribuyente = :v1 AND fechaPeriodo = :v2 AND refJurisdiccion = :v3 AND refTipo = 3 ";

   if(RG1->ItemIndex == 0)
   {
	  if(CB2->ItemIndex > 0)
		 q = q + "AND refCuentaVenta = :v4 ";
   }
   else if(RG1->ItemIndex == 1)
   {
	  if(CB2->ItemIndex > 0)
		 q = q + "AND refCuentaCompra = :v4 ";
   }

   if(idProCli > 0)
   {
	  if(RG1->ItemIndex == 0)
	  {
		 q = q + "AND refCliente = :v5 ";
	  }
	  else if(RG1->ItemIndex == 1)
	  {
		 q = q + "AND refProveedor = :v5 ";
      }
   }

   if(CkB1->Checked)
	  q = q + "AND RetencionesIVA > 0 ";
   if(CkB2->Checked)
	  q = q + "AND PercepcionesIVA > 0 ";
   if(CkB3->Checked)
	  q = q + "AND RetencionesIB > 0 ";
   if(CkB4->Checked)
	  q = q + "AND PercepcionesIB > 0 ";
   if(CkB5->Checked)
	  q = q + "AND RetencionesGanancias > 0 ";


   AuxQuery->Close();
   AuxQuery->SQL->Clear();
   AuxQuery->SQL->Add(q);
   AuxQuery->ParamByName("v1")->AsInteger = idContribuyente;
   AuxQuery->ParamByName("v2")->AsDate = StrToDate("01/" + EdPeriodo->Text);
   if(CB1->ItemIndex > 0)
	  AuxQuery->ParamByName("v3")->AsInteger = idJurisdiccion;
   if(CB2->ItemIndex > 0)
	  AuxQuery->ParamByName("v4")->AsInteger = idCuenta;
   if(idProCli > 0)
      AuxQuery->ParamByName("v5")->AsInteger = idProCli;
   AuxQuery->Open();

   AuxQuery->ParamByName("v1")->AsInteger = idContribuyente;

   Label40->Caption = FormatFloat("$ 0.#0", AuxQuery->FieldByName("totC")->AsFloat);

   AuxQuery->Close();




//**********************************************************



}
//---------------------------------------------------------------------------

void TReportes::Mostrar(void)
{
   if(idContribuyente == 0 || !perOK)
	  return;

   Query1->Close();
   CDS->Close();

   if(RG1->ItemIndex == 0)
   {
	  DBG1->Columns->Items[1]->Title->Caption = "Cliente";
	  DBG1->Columns->Items[1]->FieldName = "cliente";
	  DBG1->Columns->Items[6]->FieldName = "desCuentaVenta";
	  CDSdesCuentaCompra->FieldName = "desCuentaVenta";
	  CDSproveedor->FieldName = "cliente";
	  Label38->Caption = "Cliente:";
	  Button3->Enabled = true;
	  Button4->Enabled = false;
   }
   else if(RG1->ItemIndex == 1)
   {
	  DBG1->Columns->Items[1]->Title->Caption = "Proveedor";
	  DBG1->Columns->Items[1]->FieldName = "proveedor";
	  DBG1->Columns->Items[6]->FieldName = "desCuentaCompra";
	  CDSdesCuentaCompra->FieldName = "desCuentaCompra";
	  CDSproveedor->FieldName = "proveedor";
	  Label38->Caption = "Proveedor:";
	  Button3->Enabled = false;
	  Button4->Enabled = true;
   }

   CkB1->Checked = false;
   CkB2->Checked = false;
   CkB3->Checked = false;
   CkB4->Checked = false;
   CkB5->Checked = false;

   Buscar();

   CargarJurisdicciones();
   CargarCuentas();


   EdProCli->Enabled = true;
}
//---------------------------------------------------------------------------

void TReportes::CargarJurisdicciones(void)
{
   AnsiString q;

   if(RG1->ItemIndex == 0)
   {
	   q = "SELECT DISTINCT (SELECT desJurisdiccion FROM jurisdicciones WHERE comprobantesVentas.refJurisdiccion = jurisdicciones.idJurisdiccion) AS jurisdiccion ";
	   q = q + "FROM comprobantesVentas ";
   }
   else if(RG1->ItemIndex == 1)
   {
	  q = "SELECT DISTINCT (SELECT desJurisdiccion FROM jurisdicciones WHERE comprobantesCompras.refJurisdiccion = jurisdicciones.idJurisdiccion) AS jurisdiccion ";
	  q = q + "FROM comprobantesCompras ";
   }

   q = q + "WHERE refContribuyente = :v1 AND fechaPeriodo = :v2 ";

   AuxQuery->Close();
   AuxQuery->SQL->Clear();
   AuxQuery->SQL->Add(q);
   AuxQuery->ParamByName("v1")->AsInteger = idContribuyente;
   AuxQuery->ParamByName("v2")->AsDate = StrToDate("01/" + EdPeriodo->Text);
   AuxQuery->Open();
   AuxQuery->First();
   CB1->Clear();
   CB1->Items->Add("Todas");
   while(!AuxQuery->Eof)
   {
	  CB1->Items->Add(AuxQuery->FieldByName("jurisdiccion")->AsString);
	  AuxQuery->Next();
   }
   AuxQuery->Close();

   CB1->ItemIndex = 0;

   if(CB1->Items->Count > 1)
	  CB1->Enabled = true;
   else
	  CB1->Enabled = false;
}
//---------------------------------------------------------------------------

void TReportes::CargarCuentas(void)
{
   AnsiString q;
   int idJurisdiccion;

   if(RG1->ItemIndex == 0)
   {
	   q = "SELECT DISTINCT (SELECT desCuentaVenta FROM cuentasventas WHERE comprobantesventas.refCuentaVenta = cuentasventas.idCuentaVenta) AS cuenta ";
	   q = q + "FROM comprobantesVentas ";
   }
   else if(RG1->ItemIndex == 1)
   {
	  q = "SELECT DISTINCT (SELECT desCuentaCompra FROM cuentascompras WHERE comprobantescompras.refCuentaCompra = cuentascompras.idCuentaCompra) AS cuenta ";
	  q = q + "FROM comprobantescompras ";
   }

   if(CB1->ItemIndex <= 0)
	  q = q + "WHERE refContribuyente = :v1 AND fechaPeriodo = :v2 ";
   else
   {
      AuxQuery->Close();
	  AuxQuery->SQL->Clear();
	  AuxQuery->SQL->Add("SELECT idJurisdiccion FROM jurisdicciones WHERE desJurisdiccion = :v");
	  AuxQuery->ParamByName("v")->AsString = CB1->Items->Strings[CB1->ItemIndex];
	  AuxQuery->Open();
	  idJurisdiccion = AuxQuery->FieldByName("idJurisdiccion")->AsInteger;
	  AuxQuery->Close();

	  q = q + "WHERE refContribuyente = :v1 AND fechaPeriodo = :v2 AND refJurisdiccion = :v3";
   }

   AuxQuery->Close();
   AuxQuery->SQL->Clear();
   AuxQuery->SQL->Add(q);
   AuxQuery->ParamByName("v1")->AsInteger = idContribuyente;
   AuxQuery->ParamByName("v2")->AsDate = StrToDate("01/" + EdPeriodo->Text);
   if(CB1->ItemIndex > 0)
      AuxQuery->ParamByName("v3")->AsInteger = idJurisdiccion;

   AuxQuery->Open();
   AuxQuery->First();
   CB2->Clear();
   CB2->Items->Add("Todas");
   while(!AuxQuery->Eof)
   {
	  CB2->Items->Add(AuxQuery->FieldByName("cuenta")->AsString);
	  AuxQuery->Next();
   }
   AuxQuery->Close();

   CB2->ItemIndex = 0;

   if(CB2->Items->Count > 1)
	  CB2->Enabled = true;
   else
	  CB2->Enabled = false;
}

//---------------------------------------------------------------------------


void __fastcall TReportes::EdContribuyenteKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(Key == VK_BACK)
   {
	  Key = NULL;
	  EdContribuyente->Text = "___-________-_";
	  EdContribuyente->SelStart = 0;
   }
   else if(Key == VK_DELETE)
   {
	  Key = NULL;
	  EdContribuyente->Text = "__-________-_";
	  EdContribuyente->SelStart = 0;
   }
}
//---------------------------------------------------------------------------

void __fastcall TReportes::EdContribuyenteKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
	  Opciones->llamador = 7;
	  Opciones->soloMisClientes = true;
	  Opciones->ShowModal();
	  Key = NULL;

	  AuxQuery->Close();
	  AuxQuery->SQL->Clear();
	  AuxQuery->SQL->Add("SELECT cuit FROM Contribuyentes WHERE(idContribuyente = :v)");
	  AuxQuery->ParamByName("v")->AsInteger = Opciones->idRetorno;
	  AuxQuery->Open();
	  EdContribuyente->Text = AuxQuery->FieldByName("cuit")->AsString;
	  AuxQuery->Close();

	  if(EdContribuyente->Text == "")
	     EdContribuyente->Text = "__-________-_";

	  EdPeriodo->SetFocus();
   }

   EdContribuyente->SelLength = 1;
}
//---------------------------------------------------------------------------

void __fastcall TReportes::EdContribuyenteKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(EdContribuyente->SelStart == 2 || EdContribuyente->SelStart == 11)
	  EdContribuyente->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TReportes::EdContribuyenteMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   if(EdContribuyente->SelStart == 2 || EdContribuyente->SelStart == 11)
	  EdContribuyente->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TReportes::EdContribuyenteExit(TObject *Sender)
{
   VerificarDatos(Sender);
   Mostrar();
}
//---------------------------------------------------------------------------

void __fastcall TReportes::EdPeriodoExit(TObject *Sender)
{
   VerificarDatos(Sender);
   if(conOK && perOK)
	  Mostrar();
   else
      CDS->Close();
}
//---------------------------------------------------------------------------

void __fastcall TReportes::EdPeriodoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(Key == VK_UP)
   {
      Key = NULL;
	  if(perOK)
	  {
		 TDateTime fecha;
		 fecha = StrToDate("01/" + EdPeriodo->Text);
		 fecha = IncMonth(fecha,1);

		 EdPeriodo->Text = FormatDateTime("mm/yyyy", fecha);


		 if(conOK && perOK)
			Mostrar();
		 else
			CDS->Close();
      }
   }
   else if(Key == VK_DOWN)
   {
	  Key = NULL;
	  if(perOK)
	  {
		 TDateTime fecha;
		 fecha = StrToDate("01/" + EdPeriodo->Text);
		 fecha = IncMonth(fecha,-1);

		 EdPeriodo->Text = FormatDateTime("mm/yyyy", fecha);


		 if(conOK && perOK)
			Mostrar();
		 else
			CDS->Close();
	  }
   }
   else if(Key == VK_BACK)
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

void __fastcall TReportes::EdPeriodoKeyPress(TObject *Sender, System::WideChar &Key)

{
   EdPeriodo->SelLength = 1;
}
//---------------------------------------------------------------------------

void __fastcall TReportes::EdPeriodoKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(EdPeriodo->SelStart == 2)
	  EdPeriodo->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TReportes::EdPeriodoMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   if(EdPeriodo->SelStart == 2)
	  EdPeriodo->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TReportes::FormShow(TObject *Sender)
{
   RestablecerFormulario();
}
//---------------------------------------------------------------------------

void __fastcall TReportes::FormClose(TObject *Sender, TCloseAction &Action)
{
   Query1->Close();
}
//---------------------------------------------------------------------------


void __fastcall TReportes::CB1Change(TObject *Sender)
{
   CB2->ItemIndex = 0;
   Buscar();

   CargarCuentas();
}
//---------------------------------------------------------------------------


void __fastcall TReportes::CB2Change(TObject *Sender)
{
   Buscar();
}
//---------------------------------------------------------------------------


void __fastcall TReportes::RG1Click(TObject *Sender)
{
   if(conOK && perOK)
      Mostrar();
}
//---------------------------------------------------------------------------

void __fastcall TReportes::EdProCliKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(Key == VK_BACK)
   {
	  Key = NULL;
	  EdProCli->Text = "___-________-_";
	  EdProCli->SelStart = 0;
   }
   else if(Key == VK_DELETE)
   {
	  Key = NULL;
	  EdProCli->Text = "__-________-_";
	  EdProCli->SelStart = 0;
   }
}
//---------------------------------------------------------------------------

void __fastcall TReportes::EdProCliKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
	  Opciones->llamador = 7;
	  Opciones->ShowModal();
	  Key = NULL;

	  AuxQuery->Close();
	  AuxQuery->SQL->Clear();
	  AuxQuery->SQL->Add("SELECT cuit FROM Contribuyentes WHERE(idContribuyente = :v)");
	  AuxQuery->ParamByName("v")->AsInteger = Opciones->idRetorno;
	  AuxQuery->Open();
	  EdProCli->Text = AuxQuery->FieldByName("cuit")->AsString;
	  AuxQuery->Close();

	  if(EdProCli->Text == "")
		 EdProCli->Text = "__-________-_";
   }

   EdProCli->SelLength = 1;
}
//---------------------------------------------------------------------------

void __fastcall TReportes::EdProCliKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(EdProCli->SelStart == 2 || EdProCli->SelStart == 11)
	  EdProCli->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TReportes::EdProCliMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
   if(EdProCli->SelStart == 2 || EdProCli->SelStart == 11)
	  EdProCli->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TReportes::EdProCliExit(TObject *Sender)
{
   VerificarDatos(Sender);
   Buscar();
}
//---------------------------------------------------------------------------

void __fastcall TReportes::Button3Click(TObject *Sender)
{
   AnsiString q;

   q = "SELECT fechaComprobante, ptoVenta, nroComprobante, idTipo, idDocumento, ";
   q = q + "(SELECT razonSocial FROM contribuyentes WHERE refContribuyente = idContribuyente) AS contribuyente, ";
   if(RG1->ItemIndex == 0)
   {
	  q = q + "(SELECT razonSocial FROM contribuyentes WHERE refCliente = idContribuyente) AS cliente, ";
      q = q + "(SELECT cuit FROM contribuyentes WHERE refCliente = idContribuyente) AS cuit, ";
	  q = q + "desTipo, desDocumento, desCuentaVenta, ";
   }
   if(RG1->ItemIndex == 1)
   {
	  q = q + "(SELECT razonSocial FROM contribuyentes WHERE refProveedor = idContribuyente) AS proveedor, ";
      q = q + "(SELECT cuit FROM contribuyentes WHERE refProveedor = idContribuyente) AS cuit, ";
	  q = q + "desTipo, desDocumento, desCuentaCompra, ";
   }

   q = q + "netoGravado1, netoGravado2, netoGravado3, netoGravado4,";
   q = q + "retencionesIVA, percepcionesIVA, retencionesIB, percepcionesIB, retencionesGanancias, ";
   q = q + "conceptosNoGravados, exentos, total, desJurisdiccion ";
   if(RG1->ItemIndex == 0)
   {
	  q = q + "FROM comprobantesVentas ";
	  q = q + "INNER JOIN tipos ON comprobantesVentas.refTipo = tipos.idTipo ";
	  q = q + "INNER JOIN documentos ON comprobantesVentas.refDocumento = documentos.idDocumento ";
	  q = q + "INNER JOIN cuentasVentas ON comprobantesVentas.refCuentaVenta = cuentasVentas.idCuentaVenta ";
	  q = q + "INNER JOIN jurisdicciones ON comprobantesVentas.refJurisdiccion = jurisdicciones.idJurisdiccion ";
   }
   else if(RG1->ItemIndex == 1)
   {
	  q = q + "FROM comprobantesCompras ";
	  q = q + "INNER JOIN tipos ON comprobantesCompras.refTipo = tipos.idTipo ";
	  q = q + "INNER JOIN documentos ON comprobantesCompras.refDocumento = documentos.idDocumento ";
	  q = q + "INNER JOIN cuentasCompras ON comprobantesCompras.refCuentaCompra = cuentasCompras.idCuentaCompra ";
	  q = q + "INNER JOIN jurisdicciones ON comprobantesCompras.refJurisdiccion = jurisdicciones.idJurisdiccion ";
   }

   q = q + "WHERE refContribuyente = :v1 AND fechaPeriodo = :v2 ";

   q = q + "ORDER BY fechaComprobante ASC ";


   AuxQuery->Close();
   AuxQuery->SQL->Clear();
   AuxQuery->SQL->Add(q);
   AuxQuery->ParamByName("v1")->AsInteger = idContribuyente;
   AuxQuery->ParamByName("v2")->AsDate = StrToDate("01/" + EdPeriodo->Text);
   AuxQuery->Open();

//-----------------------------------------------------------------------------


   if(AuxQuery->IsEmpty())
	  return;

   AnsiString dir = "no_dir";
   if(SaveDialog1->Execute())
	  dir = SaveDialog1->FileName;

   if (dir == "no_dir")
      return;


   TStringList *VentasComp;
   VentasComp = new TStringList();
   TStringList *VentasAlic;
   VentasAlic = new TStringList();




   AnsiString r;
   AnsiString s, c, ng1, ng2, ng3;
   int idTipo, idDocumento;
   int i;
   VentasComp->Clear();
   VentasAlic->Clear();

   AuxQuery->First();

   while(!AuxQuery->Eof)      // para ventas
   {
	  r = FormatDateTime("yyyymmdd", AuxQuery->FieldByName("fechaComprobante")->AsDateTime);  //1

	  idTipo = AuxQuery->FieldByName("idTipo")->AsInteger;
	  idDocumento = AuxQuery->FieldByName("idDocumento")->AsInteger;

	  switch(idTipo)
	  {
	  case 1:
	  {
		  switch(idDocumento)
		  {
			 case 1: s = "001"; break;
			 case 2: s = "081"; break;
			 case 3: s = "003"; break;
			 case 4: s = "002"; break;
			 case 5: s = "004"; break;
			 default: s = "000"; break;
		  }
	  } break;
	  case 2:
	  {
		  switch(idDocumento)
		  {
			 case 1: s = "006"; break;
			 case 2: s = "082"; break;
			 case 3: s = "008"; break;
			 case 4: s = "007"; break;
			 case 5: s = "009"; break;
			 default: s = "000"; break;
  		  }
	  } break;
	  case 5:
	  {
		  switch(idDocumento)
		  {
			 case 1: s = "051"; break;
			 case 2: s = "118"; break;
			 case 3: s = "053"; break;
			 case 4: s = "052"; break;
			 case 5: s = "054"; break;
			 default: s = "000"; break;
		  }
	  } break;
	  case 6:
	  {
		  switch(idDocumento)
		  {
			 case 2: s = "082"; break;
			 default: s = "000"; break;
          }
	  } break;
	  default: s = "000"; break;
      }

	  r = r + s;                       //2

	  s = AuxQuery->FieldByName("ptoVenta")->AsString;
	  while(s.Length() < 5)
		 s = s.Insert("0",1);
	  r = r + s;                       //3

	  s = AuxQuery->FieldByName("nroComprobante")->AsString;
	  while(s.Length() < 20)
		 s = s.Insert("0",1);
	  r = r + s + s;                   //4 y 5

	  if(AuxQuery->FieldByName("cuit")->AsString == "00-00000000-0")
		 r = r + "99";
	  else
		 r = r + "80";                 //6

	  s = AuxQuery->FieldByName("cuit")->AsString;
	  s = s.Delete(3,1);
	  s = s.Delete(11,1);

      while(s.Length() < 20)
		 s = s.Insert("0",1);

	  r = r + s;                       //7

	  s = AuxQuery->FieldByName("cliente")->AsString;
	  if(s.Length() > 30)
		 s = s.SubString(1,30);
	  else
	  {
		 while(s.Length() < 30)
			s = s.Insert(" ",s.Length()+1);
	  }
	  r = r + s;                       //8

	  s = FormatFloat("0.#0", AuxQuery->FieldByName("total")->AsFloat);
	  if(s.Pos("-"))
		 s.Delete(1,1);
	  s = s.Delete(s.Length()-2,1);
	  while(s.Length() < 15)
		 s = s.Insert("0",1);
	  r = r + s;                       //9

	  s = FormatFloat("0.#0", AuxQuery->FieldByName("conceptosNoGravados")->AsFloat);
	  if(s.Pos("-"))
		 s.Delete(1,1);
	  s = s.Delete(s.Length()-2,1);
	  while(s.Length() < 15)
		 s = s.Insert("0",1);
	  r = r + s;                      //10

      r = r + "000000000000000";      //11

	  s = FormatFloat("0.#0", AuxQuery->FieldByName("exentos")->AsFloat);
	  if(s.Pos("-"))
		 s.Delete(1,1);
	  s = s.Delete(s.Length()-2,1);
	  while(s.Length() < 15)
		 s = s.Insert("0",1);
	  r = r + s;                      //12

	  s = FormatFloat("0.#0", AuxQuery->FieldByName("percepcionesIVA")->AsFloat + AuxQuery->FieldByName("retencionesIVA")->AsFloat + AuxQuery->FieldByName("retencionesGanancias")->AsFloat);
	  if(s.Pos("-"))
		 s.Delete(1,1);
	  s = s.Delete(s.Length()-2,1);
	  while(s.Length() < 15)
		 s = s.Insert("0",1);
	  r = r + s;                      //13

	  s = FormatFloat("0.#0", AuxQuery->FieldByName("percepcionesIB")->AsFloat + AuxQuery->FieldByName("retencionesIB")->AsFloat);
	  if(s.Pos("-"))
		 s.Delete(1,1);
	  s = s.Delete(s.Length()-2,1);
	  while(s.Length() < 15)
		 s = s.Insert("0",1);
	  r = r + s;                     //14

	  r = r + "000000000000000";     //15

	  r = r + "000000000000000";     //16

	  r = r + "PES";                 //17 codigo moneda

	  r = r + "0001000000";          // 18 tipo de cambio

	  ng1 = FormatFloat("0.#0", AuxQuery->FieldByName("netoGravado1")->AsFloat);
	  if(ng1.Pos("-"))
		 ng1.Delete(1,1);
	  ng2 = FormatFloat("0.#0", AuxQuery->FieldByName("netoGravado2")->AsFloat);
	  if(ng2.Pos("-"))
		 ng2.Delete(1,1);
	  ng3 = FormatFloat("0.#0", AuxQuery->FieldByName("netoGravado3")->AsFloat);
	  if(ng3.Pos("-"))
		 ng3.Delete(1,1);

	  i = 0;
	  if(ng1 != "0,00")
		 i++;
	  if(ng2 != "0,00")
		 i++;
	  if(ng3 != "0,00")
		 i++;

	  r = r + IntToStr(i);          //19

	  r = r + " ";                  //20 codigo operacion      OJO! HAY QUE REVISAR ESTO SEGUN TABLA CODIGOS DE OPERACION DE AFIP. POR AHORA FUNCIONA BIEN ASI

	  r = r + "000000000000000";    //21

	  //r = r + FormatDateTime("yyyymmdd", AuxQuery->FieldByName("fechaComprobante")->AsDateTime);

      r = r + "00000000";           //22 fecha vencimiento pago

	  VentasComp->Add(r);


	  if(ng1 != "0,00")       //21%
	  {
		 c = r.SubString(9,28);
		 s = ng1.Delete(ng1.Length()-2,1);
		 while(s.Length() < 15)
			s = s.Insert("0",1);
		 c = c + s;
		 c = c + "0005";
		 s = FormatFloat("0.#0", 0.21 * AuxQuery->FieldByName("netoGravado1")->AsFloat);
		 if(s.Pos("-"))
			s.Delete(1,1);
		 s = s.Delete(s.Length()-2,1);
		 while(s.Length() < 15)
			s = s.Insert("0",1);
		 c = c + s;
		 VentasAlic->Add(c);
	  }
	  if(ng2 != "0,00")      //10.5%
	  {
		 c = r.SubString(9,28);
		 s = ng2.Delete(ng2.Length()-2,1);
		 while(s.Length() < 15)
			s = s.Insert("0",1);
		 c = c + s;
		 c = c + "0004";
		 s = FormatFloat("0.#0", 0.105 * AuxQuery->FieldByName("netoGravado2")->AsFloat);
		 if(s.Pos("-"))
		    s.Delete(1,1);
		 s = s.Delete(s.Length()-2,1);
		 while(s.Length() < 15)
			s = s.Insert("0",1);
		 c = c + s;
		 VentasAlic->Add(c);
	  }
	  if(ng3 != "0,00")      //27%
	  {
		 c = r.SubString(9,28);
		 s = ng3.Delete(ng3.Length()-2,1);
		 while(s.Length() < 15)
			s = s.Insert("0",1);
		 c = c + s;
		 c = c + "0006";
		 s = FormatFloat("0.#0", 0.27 * AuxQuery->FieldByName("netoGravado3")->AsFloat);
		 if(s.Pos("-"))
		    s.Delete(1,1);
		 s = s.Delete(s.Length()-2,1);
         while(s.Length() < 15)
			s = s.Insert("0",1);
		 c = c + s;
		 VentasAlic->Add(c);
	  }

	  AuxQuery->Next();
   }
   VentasComp->SaveToFile(dir + " - VentasComp.txt");
   VentasAlic->SaveToFile(dir + " - VentasAlic.txt");

   delete VentasComp;
   delete VentasAlic;

   Application->MessageBox(L"Los comprobantes fueron generados exitosamente",L"Operación finalizada",MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1);
}
//---------------------------------------------------------------------------

void TReportes::RestablecerFormulario(void)
{
   idContribuyente = 0;
   idProCli = 0;
   perOK = false;
   conOK = false;
   procliOK = false;

   Label14->Caption = "-";
   Label15->Caption = "-";
   Label16->Caption = "-";
   Label18->Caption = "-";
   Label19->Caption = "-";
   Label20->Caption = "-";
   Label21->Caption = "-";
   Label22->Caption = "-";
   Label23->Caption = "-";
   Label24->Caption = "-";
   Label25->Caption = "-";
   Label26->Caption = "-";
   Label27->Caption = "-";
   Label28->Caption = "-";
   Label37->Caption = "-";
   Label40->Caption = "-";
   desContribuyente->Caption = "-";
   desProCli->Caption = "-";
   EdContribuyente->Text = "__-________-_";
   EdProCli->Text = "__-________-_";
   EdPeriodo->Text = "__/____";
   Edit1->Text = "";
   Edit2->Text = "";
   CB1->Text = "";
   CB1->Enabled = false;
   CB2->Text = "";
   CB2->Enabled = false;
   CB1->Text = "";
   RG1->ItemIndex = 0;
   //RG1->Enabled = false;
   CkB1->Checked = false;
   CkB2->Checked = false;
   CkB3->Checked = false;
   CkB4->Checked = false;
   CkB5->Checked = false;

   CDS->Close();

   Button3->Enabled = true;
   Button4->Enabled = false;

   EdContribuyente->SetFocus();
}

//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TReportes::Button4Click(TObject *Sender)
{
   AnsiString q;

   q = "SELECT fechaComprobante, ptoVenta, nroComprobante, idTipo, idDocumento, ";
   q = q + "(SELECT razonSocial FROM contribuyentes WHERE refContribuyente = idContribuyente) AS contribuyente, ";
   if(RG1->ItemIndex == 0)
   {
	  q = q + "(SELECT razonSocial FROM contribuyentes WHERE refCliente = idContribuyente) AS cliente, ";
      q = q + "(SELECT cuit FROM contribuyentes WHERE refCliente = idContribuyente) AS cuit, ";
	  q = q + "desTipo, desDocumento, desCuentaVenta, ";
   }
   if(RG1->ItemIndex == 1)
   {
	  q = q + "(SELECT razonSocial FROM contribuyentes WHERE refProveedor = idContribuyente) AS proveedor, ";
      q = q + "(SELECT cuit FROM contribuyentes WHERE refProveedor = idContribuyente) AS cuit, ";
	  q = q + "desTipo, desDocumento, desCuentaCompra, ";
   }

   q = q + "netoGravado1, netoGravado2, netoGravado3, netoGravado4,";
   q = q + "retencionesIVA, percepcionesIVA, retencionesIB, percepcionesIB, retencionesGanancias, ";
   q = q + "conceptosNoGravados, exentos, total, desJurisdiccion ";
   if(RG1->ItemIndex == 0)
   {
	  q = q + "FROM comprobantesVentas ";
	  q = q + "INNER JOIN tipos ON comprobantesVentas.refTipo = tipos.idTipo ";
	  q = q + "INNER JOIN documentos ON comprobantesVentas.refDocumento = documentos.idDocumento ";
	  q = q + "INNER JOIN cuentasVentas ON comprobantesVentas.refCuentaVenta = cuentasVentas.idCuentaVenta ";
	  q = q + "INNER JOIN jurisdicciones ON comprobantesVentas.refJurisdiccion = jurisdicciones.idJurisdiccion ";
   }
   else if(RG1->ItemIndex == 1)
   {
	  q = q + "FROM comprobantesCompras ";
	  q = q + "INNER JOIN tipos ON comprobantesCompras.refTipo = tipos.idTipo ";
	  q = q + "INNER JOIN documentos ON comprobantesCompras.refDocumento = documentos.idDocumento ";
	  q = q + "INNER JOIN cuentasCompras ON comprobantesCompras.refCuentaCompra = cuentasCompras.idCuentaCompra ";
	  q = q + "INNER JOIN jurisdicciones ON comprobantesCompras.refJurisdiccion = jurisdicciones.idJurisdiccion ";
   }

   q = q + "WHERE refContribuyente = :v1 AND fechaPeriodo = :v2 ";

   q = q + "ORDER BY fechaComprobante ASC ";


   AuxQuery->Close();
   AuxQuery->SQL->Clear();
   AuxQuery->SQL->Add(q);
   AuxQuery->ParamByName("v1")->AsInteger = idContribuyente;
   AuxQuery->ParamByName("v2")->AsDate = StrToDate("01/" + EdPeriodo->Text);
   AuxQuery->Open();

//-----------------------------------------------------------------------------

   if(AuxQuery->IsEmpty())
	  return;

   AnsiString dir = "no_dir";
   if(SaveDialog1->Execute())
	  dir = SaveDialog1->FileName;

   if (dir == "no_dir")
	  return;


   TStringList *ComprasComp;
   ComprasComp = new TStringList();
   TStringList *ComprasAlic;
   ComprasAlic = new TStringList();


   AnsiString r;
   AnsiString s, c, ng1, ng2, ng3;
   int idTipo, idDocumento;
   int i;
   ComprasComp->Clear();
   ComprasAlic->Clear();

   AuxQuery->First();

   while(!AuxQuery->Eof)      // para Compras
   {
	  r = FormatDateTime("yyyymmdd", AuxQuery->FieldByName("fechaComprobante")->AsDateTime);  //1

	  idTipo = AuxQuery->FieldByName("idTipo")->AsInteger;
	  idDocumento = AuxQuery->FieldByName("idDocumento")->AsInteger;

	  switch(idTipo)
	  {
	  case 1:
	  {
		  switch(idDocumento)
		  {
			 case 1: s = "001"; break;
			 case 2: s = "081"; break;
			 case 3: s = "003"; break;
			 case 4: s = "002"; break;
			 case 5: s = "004"; break;
			 default: s = "000"; break;
		  }
	  } break;
	  case 2:
	  {
		  switch(idDocumento)
		  {
			 case 1: s = "006"; break;
			 case 2: s = "082"; break;
			 case 3: s = "008"; break;
			 case 4: s = "007"; break;
			 case 5: s = "009"; break;
			 default: s = "000"; break;
		  }
	  } break;
	  case 3:
	  {
		  switch(idDocumento)
		  {
			 case 1: s = "011"; break;
			 //case 2: s = "082"; break;	//esto no es valido
			 case 3: s = "013"; break;
			 case 4: s = "012"; break;
			 case 5: s = "015"; break;
			 default: s = "000"; break;
		  }
	  } break;
	  case 5:
	  {
		  switch(idDocumento)
		  {
			 case 1: s = "051"; break;
			 case 2: s = "118"; break;
			 case 3: s = "053"; break;
			 case 4: s = "052"; break;
			 case 5: s = "054"; break;
			 default: s = "000"; break;
		  }
	  } break;
	  default: s = "000"; break;
      }

	  r = r + s;                       //2

	  s = AuxQuery->FieldByName("ptoVenta")->AsString;
	  while(s.Length() < 5)
		 s = s.Insert("0",1);
	  r = r + s;                       //3

	  s = AuxQuery->FieldByName("nroComprobante")->AsString;
	  while(s.Length() < 20)
		 s = s.Insert("0",1);
	  r = r + s;                   //4

	  r = r + "                ";                   //5

	  if(AuxQuery->FieldByName("cuit")->AsString == "00-00000000-0")
		 r = r + "99";
	  else
		 r = r + "80";                 //6

	  s = AuxQuery->FieldByName("cuit")->AsString;
	  s = s.Delete(3,1);
	  s = s.Delete(11,1);

      while(s.Length() < 20)
		 s = s.Insert("0",1);

	  r = r + s;                       //7

	  s = AuxQuery->FieldByName("proveedor")->AsString;
	  if(s.Length() > 30)
		 s = s.SubString(1,30);
	  else
	  {
		 while(s.Length() < 30)
			s = s.Insert(" ",s.Length()+1);
	  }
	  r = r + s;                       //8

	  s = FormatFloat("0.#0", AuxQuery->FieldByName("total")->AsFloat);
	  if(s.Pos("-"))
		 s.Delete(1,1);
	  s = s.Delete(s.Length()-2,1);
	  while(s.Length() < 15)
		 s = s.Insert("0",1);
	  r = r + s;                       //9

	  s = FormatFloat("0.#0", AuxQuery->FieldByName("conceptosNoGravados")->AsFloat);
	  if(s.Pos("-"))
		 s.Delete(1,1);
	  s = s.Delete(s.Length()-2,1);
	  while(s.Length() < 15)
		 s = s.Insert("0",1);
	  r = r + s;                      //10

	  s = FormatFloat("0.#0", AuxQuery->FieldByName("exentos")->AsFloat);
	  if(s.Pos("-"))
		 s.Delete(1,1);
	  s = s.Delete(s.Length()-2,1);
	  while(s.Length() < 15)
		 s = s.Insert("0",1);
	  r = r + s;                      //11

	  s = FormatFloat("0.#0", AuxQuery->FieldByName("percepcionesIVA")->AsFloat + AuxQuery->FieldByName("retencionesIVA")->AsFloat);
      if(s.Pos("-"))
		 s.Delete(1,1);
	  s = s.Delete(s.Length()-2,1);
	  while(s.Length() < 15)
		 s = s.Insert("0",1);
	  r = r + s;                      //12

	  s = FormatFloat("0.#0", AuxQuery->FieldByName("retencionesGanancias")->AsFloat);
      if(s.Pos("-"))
		 s.Delete(1,1);
	  s = s.Delete(s.Length()-2,1);
	  while(s.Length() < 15)
		 s = s.Insert("0",1);
	  r = r + s;                      //13

	  s = FormatFloat("0.#0", AuxQuery->FieldByName("percepcionesIB")->AsFloat + AuxQuery->FieldByName("retencionesIB")->AsFloat);
      if(s.Pos("-"))
		 s.Delete(1,1);
	  s = s.Delete(s.Length()-2,1);
	  while(s.Length() < 15)
		 s = s.Insert("0",1);
	  r = r + s;                     //14

	  r = r + "000000000000000";     //15

	  r = r + "000000000000000";     //16

	  r = r + "PES";                 //17 codigo moneda

	  r = r + "0001000000";          // 18 tipo de cambio

	  ng1 = FormatFloat("0.#0", AuxQuery->FieldByName("netoGravado1")->AsFloat);
	  if(ng1.Pos("-"))
		 ng1.Delete(1,1);
	  ng2 = FormatFloat("0.#0", AuxQuery->FieldByName("netoGravado2")->AsFloat);
	  if(ng2.Pos("-"))
		 ng2.Delete(1,1);
	  ng3 = FormatFloat("0.#0", AuxQuery->FieldByName("netoGravado3")->AsFloat);
	  if(ng3.Pos("-"))
		 ng3.Delete(1,1);

	  i = 0;
	  if(ng1 != "0,00")
		 i++;
	  if(ng2 != "0,00")
		 i++;
	  if(ng3 != "0,00")
		 i++;

	  r = r + IntToStr(i);          //19

	  r = r + " ";                  //20 codigo operacion

	  s = FormatFloat("0.#0", 0.21 * AuxQuery->FieldByName("netoGravado1")->AsFloat + 0.105 * AuxQuery->FieldByName("netoGravado2")->AsFloat + 0.27 * AuxQuery->FieldByName("netoGravado3")->AsFloat);
      if(s.Pos("-"))
		 s.Delete(1,1);
	  s = s.Delete(s.Length()-2,1);
	  while(s.Length() < 15)
	     s = s.Insert("0",1);

	  r = r + s;    //21


	  r = r + "000000000000000";           //22 otros tributos

	  r = r + "00000000000";       //23 cuit emisor/corredor
	  r = r + "                              ";     //24 denominacion emisor/corredor
	  r = r + "000000000000000";                    //25 IVA comision

	  ComprasComp->Add(r);


	  if(ng1 != "0,00")       //21%
	  {
		 c = r.SubString(9,28);
		 c = c + r.SubString(53,22);
		 s = ng1.Delete(ng1.Length()-2,1);
		 while(s.Length() < 15)
			s = s.Insert("0",1);
		 c = c + s;
		 c = c + "0005";
		 s = FormatFloat("0.#0", 0.21 * AuxQuery->FieldByName("netoGravado1")->AsFloat);
         if(s.Pos("-"))
			s.Delete(1,1);
		 s = s.Delete(s.Length()-2,1);
		 while(s.Length() < 15)
			s = s.Insert("0",1);
		 c = c + s;
		 ComprasAlic->Add(c);
	  }
	  if(ng2 != "0,00")      //10.5%
	  {
		 c = r.SubString(9,28);
		 c = c + r.SubString(53,22);
		 s = ng2.Delete(ng2.Length()-2,1);
		 while(s.Length() < 15)
			s = s.Insert("0",1);
		 c = c + s;
		 c = c + "0004";
		 s = FormatFloat("0.#0", 0.105 * AuxQuery->FieldByName("netoGravado2")->AsFloat);
         if(s.Pos("-"))
		    s.Delete(1,1);
		 s = s.Delete(s.Length()-2,1);
		 while(s.Length() < 15)
			s = s.Insert("0",1);
		 c = c + s;
		 ComprasAlic->Add(c);
	  }
	  if(ng3 != "0,00")      //27%
	  {
		 c = r.SubString(9,28);
		 c = c + r.SubString(53,22);
		 s = ng3.Delete(ng3.Length()-2,1);
		 while(s.Length() < 15)
			s = s.Insert("0",1);
		 c = c + s;
		 c = c + "0006";
		 s = FormatFloat("0.#0", 0.27 * AuxQuery->FieldByName("netoGravado3")->AsFloat);
         if(s.Pos("-"))
		    s.Delete(1,1);
		 s = s.Delete(s.Length()-2,1);
		 while(s.Length() < 15)
			s = s.Insert("0",1);
		 c = c + s;
		 ComprasAlic->Add(c);
	  }

	  AuxQuery->Next();
   }
   ComprasComp->SaveToFile(dir + " - ComprasComp.txt");
   ComprasAlic->SaveToFile(dir + " - ComprasAlic.txt");


   delete ComprasComp;
   delete ComprasAlic;

   Application->MessageBox(L"Los comprobantes fueron generados exitosamente",L"Operación finalizada",MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1);
}
//---------------------------------------------------------------------------

void __fastcall TReportes::EdContribuyenteMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
   if(Button == mbRight)
   {
	  Opciones->llamador = 7;
	  Opciones->ShowModal();

	  AuxQuery->Close();
	  AuxQuery->SQL->Clear();
	  AuxQuery->SQL->Add("SELECT cuit FROM Contribuyentes WHERE(idContribuyente = :v)");
	  AuxQuery->ParamByName("v")->AsInteger = Opciones->idRetorno;
	  AuxQuery->Open();
	  EdContribuyente->Text = AuxQuery->FieldByName("cuit")->AsString;
	  AuxQuery->Close();

	  EdPeriodo->SetFocus();
   }
}
//---------------------------------------------------------------------------


void __fastcall TReportes::CkB1Click(TObject *Sender)
{
   if(idContribuyente == 0 || !perOK)
	  return;
   Buscar();
}
//---------------------------------------------------------------------------

void __fastcall TReportes::CkB2Click(TObject *Sender)
{
   if(idContribuyente == 0 || !perOK)
	  return;

   Buscar();
}
//---------------------------------------------------------------------------

void __fastcall TReportes::CkB3Click(TObject *Sender)
{
   if(idContribuyente == 0 || !perOK)
	  return;

   Buscar();
}
//---------------------------------------------------------------------------

void __fastcall TReportes::CkB4Click(TObject *Sender)
{
   if(idContribuyente == 0 || !perOK)
	  return;

   Buscar();
}
//---------------------------------------------------------------------------

void __fastcall TReportes::CkB5Click(TObject *Sender)
{
   if(idContribuyente == 0 || !perOK)
	  return;

   Buscar();
}
//---------------------------------------------------------------------------

void __fastcall TReportes::Button2Click(TObject *Sender)
{
	  if(CDS->IsEmpty())
	  	 return;

	  Variant Excel, Libro, Hoja, Celdas, Celda, Columnas;

	  Excel = Variant::CreateObject("Excel.Application");
	  Excel.OlePropertySet("Visible", true);
	  Libro=Excel.OlePropertyGet("Workbooks");
	  Libro.OleProcedure("Add");
	  Hoja=Libro.OlePropertyGet("Item",1);
	  Libro=Hoja.OlePropertyGet("Worksheets");
	  //Hoja.OleFunction("Add");
	  Hoja=Libro.OlePropertyGet("Item",1);
	  Celdas = Hoja.OlePropertyGet("Cells");
	  Columnas = Hoja.OlePropertyGet("Columns");

	  const int ri = 6;  // fila inicial para datos
	  AnsiString a;

	  a = "Fecha";
	  Celdas.OlePropertyGet("Item",ri,1).OlePropertySet("Value",StringToOleStr(a));
	  if(RG1->ItemIndex == 0)
	  a = "Cliente";
	  if(RG1->ItemIndex == 1)
	  a = "Proveedor";
	  Celdas.OlePropertyGet("Item",ri,2).OlePropertySet("Value",StringToOleStr(a));
	  a = "P. Venta";
	  Celdas.OlePropertyGet("Item",ri,3).OlePropertySet("Value",StringToOleStr(a));
	  a = "Nro Comprob";
	  Celdas.OlePropertyGet("Item",ri,4).OlePropertySet("Value",StringToOleStr(a));
	  a = "Documento";
	  Celdas.OlePropertyGet("Item",ri,5).OlePropertySet("Value",StringToOleStr(a));
	  a = "Tipo";
	  Celdas.OlePropertyGet("Item",ri,6).OlePropertySet("Value",StringToOleStr(a));
	  a = "Cuenta";
	  Celdas.OlePropertyGet("Item",ri,7).OlePropertySet("Value",StringToOleStr(a));
	  a = "Jurisdiccion";
	  Celdas.OlePropertyGet("Item",ri,8).OlePropertySet("Value",StringToOleStr(a));
	  a = "NG 21%";
	  Celdas.OlePropertyGet("Item",ri,9).OlePropertySet("Value",StringToOleStr(a));
	  a = "NG 10,5%";
	  Celdas.OlePropertyGet("Item",ri,10).OlePropertySet("Value",StringToOleStr(a));
	  a = "NG 27%";
	  Celdas.OlePropertyGet("Item",ri,11).OlePropertySet("Value",StringToOleStr(a));
	  a = "IVA Total";
	  Celdas.OlePropertyGet("Item",ri,12).OlePropertySet("Value",StringToOleStr(a));
	  a = "Ret. IVA";
	  Celdas.OlePropertyGet("Item",ri,13).OlePropertySet("Value",StringToOleStr(a));
	  a = "Perc. IVA";
	  Celdas.OlePropertyGet("Item",ri,14).OlePropertySet("Value",StringToOleStr(a));
	  a = "Ret. IIBB";
	  Celdas.OlePropertyGet("Item",ri,15).OlePropertySet("Value",StringToOleStr(a));
	  a = "Perc. IIBB";
	  Celdas.OlePropertyGet("Item",ri,16).OlePropertySet("Value",StringToOleStr(a));
	  a = "Ret. Gcias.";
	  Celdas.OlePropertyGet("Item",ri,17).OlePropertySet("Value",StringToOleStr(a));
	  a = "C.N. Grav.";
	  Celdas.OlePropertyGet("Item",ri,18).OlePropertySet("Value",StringToOleStr(a));
	  a = "Exentos";
	  Celdas.OlePropertyGet("Item",ri,19).OlePropertySet("Value",StringToOleStr(a));
	  a = "Total";
	  Celdas.OlePropertyGet("Item",ri,20).OlePropertySet("Value",StringToOleStr(a));

	  CDS->First();
	  int i=ri + 1;
	  while(!CDS->Eof)
	  {
		 Celdas.OlePropertyGet("Item",i,1).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("fechaComprobante")->AsString));

		 if(RG1->ItemIndex == 0)
			Celdas.OlePropertyGet("Item",i,2).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("cliente")->AsString));
		 if(RG1->ItemIndex == 1)
			Celdas.OlePropertyGet("Item",i,2).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("proveedor")->AsString));

		 Celdas.OlePropertyGet("Item",i,3).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("ptoVenta")->AsString));
		 Celdas.OlePropertyGet("Item",i,4).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("nroComprobante")->AsString));
		 Celdas.OlePropertyGet("Item",i,5).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("desDocumento")->AsString));
		 Celdas.OlePropertyGet("Item",i,6).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("desTipo")->AsString));

		 if(RG1->ItemIndex == 0)
			Celdas.OlePropertyGet("Item",i,7).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("desCuentaVenta")->AsString));
		 if(RG1->ItemIndex == 1)
			Celdas.OlePropertyGet("Item",i,7).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("desCuentaCompra")->AsString));

		 Celdas.OlePropertyGet("Item",i,8).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("desJurisdiccion")->AsString));
		 Celdas.OlePropertyGet("Item",i,9).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("netoGravado1")->AsString));
		 Celdas.OlePropertyGet("Item",i,10).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("netoGravado2")->AsString));
		 Celdas.OlePropertyGet("Item",i,11).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("netoGravado3")->AsString));
		 Celdas.OlePropertyGet("Item",i,12).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("totIVA")->AsString));
		 Celdas.OlePropertyGet("Item",i,13).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("retencionesIVA")->AsString));
		 Celdas.OlePropertyGet("Item",i,14).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("percepcionesIVA")->AsString));
		 Celdas.OlePropertyGet("Item",i,15).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("retencionesIB")->AsString));
		 Celdas.OlePropertyGet("Item",i,16).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("percepcionesIB")->AsString));
		 Celdas.OlePropertyGet("Item",i,17).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("retencionesGanancias")->AsString));
		 Celdas.OlePropertyGet("Item",i,18).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("conceptosNoGravados")->AsString));
		 Celdas.OlePropertyGet("Item",i,19).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("exentos")->AsString));
		 Celdas.OlePropertyGet("Item",i,20).OlePropertySet("Value",StringToOleStr(CDS->FieldByName("total")->AsString));

		 i++;
		 CDS->Next();
	  }

	  CDS->First();

	  a = "=SUMA(I2:I" + IntToStr(i-1) + ")";
	  Celdas.OlePropertyGet("Item",i+1,9).OlePropertySet("Value",StringToOleStr(a));
	  a = "=SUMA(J2:J" + IntToStr(i-1) + ")";
	  Celdas.OlePropertyGet("Item",i+1,10).OlePropertySet("Value",StringToOleStr(a));
	  a = "=SUMA(K2:K" + IntToStr(i-1) + ")";
	  Celdas.OlePropertyGet("Item",i+1,11).OlePropertySet("Value",StringToOleStr(a));
	  a = "=SUMA(L2:L" + IntToStr(i-1) + ")";
	  Celdas.OlePropertyGet("Item",i+1,12).OlePropertySet("Value",StringToOleStr(a));
	  a = "=SUMA(M2:M" + IntToStr(i-1) + ")";
	  Celdas.OlePropertyGet("Item",i+1,13).OlePropertySet("Value",StringToOleStr(a));
	  a = "=SUMA(N2:N" + IntToStr(i-1) + ")";
	  Celdas.OlePropertyGet("Item",i+1,14).OlePropertySet("Value",StringToOleStr(a));
	  a = "=SUMA(O2:O" + IntToStr(i-1) + ")";
	  Celdas.OlePropertyGet("Item",i+1,15).OlePropertySet("Value",StringToOleStr(a));
	  a = "=SUMA(P2:P" + IntToStr(i-1) + ")";
	  Celdas.OlePropertyGet("Item",i+1,16).OlePropertySet("Value",StringToOleStr(a));
	  a = "=SUMA(Q2:Q" + IntToStr(i-1) + ")";
	  Celdas.OlePropertyGet("Item",i+1,17).OlePropertySet("Value",StringToOleStr(a));
	  a = "=SUMA(R2:R" + IntToStr(i-1) + ")";
	  Celdas.OlePropertyGet("Item",i+1,18).OlePropertySet("Value",StringToOleStr(a));
	  a = "=SUMA(S2:S" + IntToStr(i-1) + ")";
	  Celdas.OlePropertyGet("Item",i+1,19).OlePropertySet("Value",StringToOleStr(a));
	  a = "=SUMA(T2:T" + IntToStr(i-1) + ")";
	  Celdas.OlePropertyGet("Item",i+1,20).OlePropertySet("Value",StringToOleStr(a));

	  int val = i;
	  int j;

	 AnsiString formato = "#.##0,00 ;[Rojo]-#.##0,00 ";
	 a = "A" + IntToStr(ri) + ":A" + IntToStr(val-1);

	 Celda=Hoja.OlePropertyGet("Cells").OlePropertyGet("Range",StringToOleStr(a));
	 Celda.OlePropertySet("HorizontalAlignment",xlHAlignCenter);
	 a = "E2:H" + IntToStr(val-1);
	 Celda=Hoja.OlePropertyGet("Cells").OlePropertyGet("Range",StringToOleStr(a));
	 Celda.OlePropertySet("HorizontalAlignment",xlHAlignCenter);

	 a = "I" + IntToStr(ri) + ":T" + IntToStr(val+1);

	 Celda=Hoja.OlePropertyGet("Cells").OlePropertyGet("Range",StringToOleStr(a));
	 Celda.OlePropertySet("NumberFormat",StringToOleStr(formato));

	 a = "A" + IntToStr(ri) + ":T" + IntToStr(ri);

	 Celda=Hoja.OlePropertyGet("Cells").OlePropertyGet("Range",StringToOleStr(a));
	 //Celda=Hoja.OlePropertyGet("Cells").OlePropertyGet("Item",1,i);
		  //Celda.OlePropertyGet("Font").OlePropertySet("Color",clBlue);
	 Celda.OlePropertyGet("Font").OlePropertySet("Size",12);
	 Celda.OlePropertyGet("Font").OlePropertySet("Bold",true);
	 Celda.OlePropertySet("HorizontalAlignment",xlHAlignCenter);

	 Variant Column;
	 Variant EntireColumn;
	 Column=Hoja.OlePropertyGet("Columns").OlePropertyGet("Range", StringToOleStr(a));
	 EntireColumn=Column.OlePropertyGet("EntireColumn");
	 EntireColumn.OleFunction("autofit");



	 a = "A" + IntToStr(val + 1) + ":H" + IntToStr(val + 1);

	 Celda=Hoja.OlePropertyGet("Cells").OlePropertyGet("Range",StringToOleStr(a));
	 Celda.OlePropertySet("HorizontalAlignment",xlHAlignCenter);
	 Celda.OlePropertySet("MergeCells",true);
	 Celda.OlePropertyGet("Font").OlePropertySet("Bold",true);
	 a = "TOTALES:";
	 Celda.OlePropertySet("Value",StringToOleStr(a));

	  a = RG1->Items->Strings[RG1->ItemIndex].UpperCase();
	  Celdas.OlePropertyGet("Item",1,1).OlePropertySet("Value",StringToOleStr(a));
	  a = "Contribuyente: " + desContribuyente->Caption;
	  Celdas.OlePropertyGet("Item",2,1).OlePropertySet("Value",StringToOleStr(a));
	  a = "Período: " + EdPeriodo->Text;
	  Celdas.OlePropertyGet("Item",3,1).OlePropertySet("Value",StringToOleStr(a));

	 a = "A1:A3";
	  Celda=Hoja.OlePropertyGet("Cells").OlePropertyGet("Range",StringToOleStr(a));
	 //Celda=Hoja.OlePropertyGet("Cells").OlePropertyGet("Item",1,i);
		  //Celda.OlePropertyGet("Font").OlePropertySet("Color",clBlue);
	 Celda.OlePropertyGet("Font").OlePropertySet("Size",16);
	 Celda.OlePropertyGet("Font").OlePropertySet("Bold",true);
	 //Celda.OlePropertyGet("Interior").OlePropertySet("Color",clBlue);
	 //Celda.OlePropertySet("HorizontalAlignment",xlHAlignCenter);


	 a = "A1:H1";
	 Celda=Hoja.OlePropertyGet("Cells").OlePropertyGet("Range",StringToOleStr(a));
	 Celda.OlePropertySet("MergeCells",true);
	 a = "A2:H2";
	 Celda=Hoja.OlePropertyGet("Cells").OlePropertyGet("Range",StringToOleStr(a));
	 Celda.OlePropertySet("MergeCells",true);
	 a = "A3:H3";
	 Celda=Hoja.OlePropertyGet("Cells").OlePropertyGet("Range",StringToOleStr(a));
	 Celda.OlePropertySet("MergeCells",true);

	 Excel.OlePropertySet("DisplayAlerts",true);
	 Excel.OlePropertySet("Visible",true);
	 Excel = Unassigned;
}
//---------------------------------------------------------------------------


void __fastcall TReportes::Edit1Exit(TObject *Sender)
{
   if(Edit1->Text != "")
   {
       AuxQuery->Close();
	   AuxQuery->SQL->Clear();
	   AuxQuery->SQL->Add("SELECT cuit FROM Contribuyentes WHERE(idContribuyente = :v)");
	   AuxQuery->ParamByName("v")->AsString= Edit1->Text;
	   AuxQuery->Open();
	   EdContribuyente->Text = AuxQuery->FieldByName("cuit")->AsString;
	   AuxQuery->Close();

	   if(EdContribuyente->Text == "")
		 EdContribuyente->Text = "__-________-_";
   }
   EdContribuyente->SetFocus();
   Edit1->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TReportes::Edit2Exit(TObject *Sender)
{
   if(Edit2->Text != "")
   {
       AuxQuery->Close();
	   AuxQuery->SQL->Clear();
	   AuxQuery->SQL->Add("SELECT cuit FROM Contribuyentes WHERE(idContribuyente = :v)");
	   AuxQuery->ParamByName("v")->AsString= Edit2->Text;
	   AuxQuery->Open();
	   EdProCli->Text = AuxQuery->FieldByName("cuit")->AsString;
	   AuxQuery->Close();

	   if(EdProCli->Text == "")
		 EdProCli->Text = "__-________-_";
   }
   EdProCli->SetFocus();
   Edit2->Clear();
}
//---------------------------------------------------------------------------






void __fastcall TReportes::UpDown1Click(TObject *Sender, TUDBtnType Button)
{
   if(perOK)
   {
	  TDateTime fecha;
	  fecha = StrToDate("01/" + EdPeriodo->Text);
	  if(Button == btNext)
		 fecha = IncMonth(fecha,1);
	  else
		 fecha = IncMonth(fecha,-1);

	  EdPeriodo->Text = FormatDateTime("mm/yyyy", fecha);


	  if(conOK && perOK)
		 Buscar();
	  else
	     CDS->Close();
   }
}
//---------------------------------------------------------------------------


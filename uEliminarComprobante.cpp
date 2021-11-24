//---------------------------------------------------------------------------

#include <vcl.h>
#include <dateUtils.hpp>
#pragma hdrstop

#include "uEliminarComprobante.h"
#include "fOpciones.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEliminarComprobante *EliminarComprobante;
//---------------------------------------------------------------------------
__fastcall TEliminarComprobante::TEliminarComprobante(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TEliminarComprobante::VerificarDatos(TObject *Sender)
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
			 AuxQuery->SQL->Add("SELECT idContribuyente, razonSocial, refJurisdiccion FROM Contribuyentes WHERE(cuit = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				desContribuyente->Caption = AuxQuery->FieldByName("razonSocial")->AsString;
				idContribuyente = AuxQuery->FieldByName("idContribuyente")->AsInteger;
				Edit->Color = clWindow;
				contOK = true;
			 }
			 else
			 {
				desContribuyente->Caption = "Contribuyente desconocido";
				idContribuyente = 0;
				Edit->Color = clWebLightCoral;
				contOK = false;
			 }
		  }
		  else
		  {
			 desContribuyente->Caption = "";
			 Edit->Color = clWebLightCoral;
			 idContribuyente = 0;
			 contOK = false;
		  }
		  AuxQuery->Close();

	  }
	  else if(Sender == EdFecha)
	  {
		  if(Edit->Text != "__/__/____")
		  {
			 if(Edit->Text.Pos("_") > 0)
			 {
				 Edit->Color = clWebLightCoral;
				 Edit->Hint = "No se completó la fecha";
				 Edit->ShowHint =
				  true;
				 fechOK = false;
			 }
			 else if(!IsValidDate(StrToInt(Edit->Text.SubString(7,4)), StrToInt(Edit->Text.SubString(4,2)), StrToInt(Edit->Text.SubString(1,2))))
			 {
				 Edit->Color = clWebLightCoral;
				 Edit->Hint = "La fecha ingresada no es válida";
				 Edit->ShowHint = true;
				 fechOK = false;
			 }
			 else
			 {
				 Edit->Color = clWindow;
				 Edit->ShowHint = false;
				 fechOK = true;
			 }

		  }
		  else
		  {
			 Edit->Color = clWebLightCoral;
			 Edit->Hint = "No se completó la fecha";
			 Edit->ShowHint = true;
			 fechOK = false;
		  }
	  }
	  else if(Sender == EdDocumento)
	  {
		  if(Edit->Text != "")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT desDocumento FROM documentos WHERE(idDocumento = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				desDocumento->Caption = AuxQuery->FieldByName("desDocumento")->AsString;
				Edit->Color = clWindow;
				docOK = true;
			 }
			 else
			 {
				desDocumento->Caption = "No existe el indicador de documento";
				Edit->Color = clWebLightCoral;
				docOK = false;
			 }
		  }
		  else
		  {
			 desDocumento->Caption = "";
			 Edit->Color = clWebLightCoral;
			 docOK = false;
		  }
		  AuxQuery->Close();
	  }
	  else if(Sender == EdTipo)
	  {
		  if(Edit->Text != "")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT desTipo FROM tipos WHERE(idTipo = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				desTipo->Caption = AuxQuery->FieldByName("desTipo")->AsString;
				Edit->Color = clWindow;
				tipoOK = true;
			 }
			 else
			 {
				desTipo->Caption = "No existe el indicador de tipo";
				Edit->Color = clWebLightCoral;
				tipoOK = false;
			 }
		  }
		  else
		  {
			 desTipo->Caption = "";
			 Edit->Color = clWebLightCoral;
			 tipoOK = false;
		  }
		  AuxQuery->Close();
	  }
	  else if(Sender == EdPtoVenta)
	  {
		  switch(Edit->Text.Length())
		  {
			 case 0: Edit->Text = "00000"; break;
			 case 1: Edit->Text = Edit->Text.Insert("0000", 1); break;
			 case 2: Edit->Text = Edit->Text.Insert("000", 1); break;
			 case 3: Edit->Text = Edit->Text.Insert("00", 1); break;
			 case 4: Edit->Text = Edit->Text.Insert("0", 1); break;
		  }

		  if(Edit->Text != "00000")
		  {
			 Edit->Color = clWindow;
			 Edit->ShowHint = false;
			 ptoOK = true;
		  }
		  else
		  {
			 Edit->Color = clWebLightCoral;
			 Edit->Hint = "No se indica el punto de venta";
			 Edit->ShowHint = true;
			 ptoOK = false;
		  }
	  }
	  else if(Sender == EdNroComprobante)
	  {
		  switch(Edit->Text.Length())
		  {
			 case 0: Edit->Text = "00000000"; break;
			 case 1: Edit->Text = Edit->Text.Insert("0000000", 1); break;
			 case 2: Edit->Text = Edit->Text.Insert("000000", 1); break;
			 case 3: Edit->Text = Edit->Text.Insert("00000", 1); break;
			 case 4: Edit->Text = Edit->Text.Insert("0000", 1); break;
			 case 5: Edit->Text = Edit->Text.Insert("000", 1); break;
			 case 6: Edit->Text = Edit->Text.Insert("00", 1); break;
			 case 7: Edit->Text = Edit->Text.Insert("0", 1); break;
		  }

		  if(Edit->Text != "00000000")
		  {
			 Edit->Color = clWindow;
			 Edit->ShowHint = false;
			 nroOK = true;
		  }
		  else
		  {
			 Edit->Color = clWebLightCoral;
			 Edit->Hint = "No se indica el número de comprobante";
			 Edit->ShowHint = true;
			 nroOK = false;
		  }
	  }
   }
   else
	  ShowMessage("ERROR: El *Sender no es una clase TEdit");
}
//---------------------------------------------------------------------------

void TEliminarComprobante::SeleccionarTodo(TObject *Sender)
{
   if(dynamic_cast <TEdit *>(Sender) != NULL)
   {
	  TEdit *Edit = dynamic_cast <TEdit *>(Sender);
	  Edit->SelectAll();
   }
}
//---------------------------------------------------------------------------

void TEliminarComprobante::RestablecerFormulario(void)
{
	EdContribuyente->Text = "__-________-_";
	EdContribuyente->Color = clWindow;
	EdFecha->Text = "__/__/____";
	EdFecha->Color = clWindow;
	EdPtoVenta->Text = "00000";
	EdPtoVenta->Color = clWindow;
	EdNroComprobante->Text = "00000000";
	EdNroComprobante->Color = clWindow;
	EdTipo->Text = "";
	EdTipo->Color = clWindow;
	EdDocumento->Text = "";
	EdDocumento->Color = clWindow;

	desContribuyente->Caption = "-";
	desDocumento->Caption = "-";
	desTipo->Caption = "-";

	idContribuyente = 0;

	contOK = false;
	fechOK = false;
	ptoOK = false;
	nroOK = false;
	tipoOK = false;
	docOK = false;

	EdContribuyente->SetFocus();
}
//---------------------------------------------------------------------------

void TEliminarComprobante::Buscar(void)
{
   AnsiString q;

   q = "SELECT fechaComprobante, ptoVenta, nroComprobante, ";
   q = q + "(SELECT razonSocial FROM contribuyentes WHERE refContribuyente = idContribuyente) AS contribuyente, ";
   if(RG1->ItemIndex == 0)
   {
	  q = q + "(SELECT razonSocial FROM contribuyentes WHERE refCliente = idContribuyente) AS cliente, ";
	  q = q + "idComprobanteVenta, ";
   }
   if(RG1->ItemIndex == 1)
   {
	  q = q + "(SELECT razonSocial FROM contribuyentes WHERE refProveedor = idContribuyente) AS proveedor, ";
	  q = q + "idComprobanteCompra, ";
   }
   q = q + "desTipo, desDocumento, ";

   /*
   q = q + "netoGravado1, netoGravado2, netoGravado3, netoGravado4,";
   q = q + "retencionesIVA, percepcionesIVA, retencionesIB, percepcionesIB, retencionesGanancias, ";
   q = q + "conceptosNoGravados, exentos, total ";
   */
   q = q + "total ";

   if(RG1->ItemIndex == 0)
   {
	  q = q + "FROM comprobantesVentas ";
	  q = q + "INNER JOIN tipos ON comprobantesVentas.refTipo = tipos.idTipo ";
	  q = q + "INNER JOIN documentos ON comprobantesVentas.refDocumento = documentos.idDocumento ";
   }
   else if(RG1->ItemIndex == 1)
   {
	  q = q + "FROM comprobantesCompras ";
	  q = q + "INNER JOIN tipos ON comprobantesCompras.refTipo = tipos.idTipo ";
	  q = q + "INNER JOIN documentos ON comprobantesCompras.refDocumento = documentos.idDocumento ";
   }


   q = q + "WHERE refContribuyente = :v1 ";

   if(fechOK)
	  q = q + "AND fechaComprobante = :v2 ";
   if(ptoOK)
	  q = q + "AND ptoVenta = :v3 ";
   if(nroOK)
	  q = q + "AND nroComprobante = :v4 ";
   if(tipoOK)
	  q = q + "AND refTipo = :v5 ";
   if(docOK)
	  q = q + "AND refDocumento = :v6 ";

   q = q + "ORDER BY fechaComprobante ASC ";


   Query1->Close();
   Query1->SQL->Clear();
   Query1->SQL->Add(q);

   if(contOK)
	  Query1->ParamByName("v1")->AsString = idContribuyente;
   if(fechOK)
	  Query1->ParamByName("v2")->AsDate = StrToDate(EdFecha->Text);
   if(ptoOK)
	  Query1->ParamByName("v3")->AsString = EdPtoVenta->Text;
   if(nroOK)
	  Query1->ParamByName("v4")->AsString = EdNroComprobante->Text;
   if(tipoOK)
	  Query1->ParamByName("v5")->AsString = EdTipo->Text;
   if(docOK)
	  Query1->ParamByName("v6")->AsString = EdDocumento->Text;

   Query1->Open();


   ClientDataSet1->Active = false;
   ClientDataSet1->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TEliminarComprobante::FormShow(TObject *Sender)
{
   RestablecerFormulario();
}
//---------------------------------------------------------------------------
void __fastcall TEliminarComprobante::EdContribuyenteExit(TObject *Sender)
{
   VerificarDatos(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TEliminarComprobante::EdContribuyenteKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
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
void __fastcall TEliminarComprobante::EdContribuyenteKeyPress(TObject *Sender, System::WideChar &Key)

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

	  EdPtoVenta->SetFocus();
   }

   EdContribuyente->SelLength = 1;
}
//---------------------------------------------------------------------------
void __fastcall TEliminarComprobante::EdContribuyenteKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
   if(EdContribuyente->SelStart == 2 || EdContribuyente->SelStart == 11)
	  EdContribuyente->SelStart++;
}
//---------------------------------------------------------------------------
void __fastcall TEliminarComprobante::EdContribuyenteMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   if(EdContribuyente->SelStart == 2 || EdContribuyente->SelStart == 11)
	  EdContribuyente->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TEliminarComprobante::EdPtoVentaExit(TObject *Sender)
{
   VerificarDatos(Sender);
   if(contOK)
	  Buscar();
}
//---------------------------------------------------------------------------
void __fastcall TEliminarComprobante::EdPtoVentaMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TEliminarComprobante::EdNroComprobanteExit(TObject *Sender)
{
   VerificarDatos(Sender);
   if(contOK)
	  Buscar();
}
//---------------------------------------------------------------------------
void __fastcall TEliminarComprobante::EdNroComprobanteMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TEliminarComprobante::EdFechaExit(TObject *Sender)
{
   VerificarDatos(Sender);
   if(contOK)
	  Buscar();
}
//---------------------------------------------------------------------------
void __fastcall TEliminarComprobante::EdFechaKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(Key == VK_BACK)
   {
	  Key = NULL;
	  EdFecha->Text = "___/__/____";
	  EdFecha->SelStart = 0;
   }
   else if(Key == VK_DELETE)
   {
	  Key = NULL;
	  EdFecha->Text = "__/__/____";
	  EdFecha->SelStart = 0;
   }
}
//---------------------------------------------------------------------------
void __fastcall TEliminarComprobante::EdFechaKeyPress(TObject *Sender, System::WideChar &Key)

{
	  EdFecha->SelLength = 1;
}
//---------------------------------------------------------------------------
void __fastcall TEliminarComprobante::EdFechaKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(EdFecha->SelStart == 2 || EdFecha->SelStart == 5)
	  EdFecha->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TEliminarComprobante::EdDocumentoExit(TObject *Sender)
{
   VerificarDatos(Sender);
   if(contOK)
	  Buscar();
}
//---------------------------------------------------------------------------
void __fastcall TEliminarComprobante::EdDocumentoKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
	  Opciones->llamador = 3;
	  Opciones->ShowModal();
	  Key = NULL;
	  EdDocumento->Text = IntToStr(Opciones->idRetorno);
	  EdTipo->SetFocus();
   }
}
//---------------------------------------------------------------------------
void __fastcall TEliminarComprobante::EdDocumentoMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TEliminarComprobante::EdTipoExit(TObject *Sender)
{
   VerificarDatos(Sender);
   if(contOK)
	  Buscar();
}
//---------------------------------------------------------------------------
void __fastcall TEliminarComprobante::EdTipoKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
	  Opciones->llamador = 4;
	  Opciones->ShowModal();
	  Key = NULL;
	  EdTipo->Text = IntToStr(Opciones->idRetorno);
   }
}
//---------------------------------------------------------------------------
void __fastcall TEliminarComprobante::EdTipoMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TEliminarComprobante::Button2Click(TObject *Sender)
{
   if(contOK)
	  Buscar();
   else
	  Application->MessageBox(L"Debe al menos cargar el cuit del contribyente",L"Error",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
}
//---------------------------------------------------------------------------
void __fastcall TEliminarComprobante::RG1Click(TObject *Sender)
{
   ClientDataSet1->Active = false;

   if(RG1->ItemIndex == 0)
   {
	  DBGrid1->Columns->Items[1]->Title->Caption = "Cliente";
	  DBGrid1->Columns->Items[1]->FieldName = "cliente";
	  ClientDataSet1cliente->FieldName = "cliente";
	  ClientDataSet1idComprobanteVenta->FieldName = "idComprobanteVenta";
   }
   else if(RG1->ItemIndex == 1)
   {
	  DBGrid1->Columns->Items[1]->Title->Caption = "Proveedor";
	  DBGrid1->Columns->Items[1]->FieldName = "proveedor";
	  ClientDataSet1cliente->FieldName = "proveedor";
	  ClientDataSet1idComprobanteVenta->FieldName = "idComprobanteCompra";
   }

   if(contOK)
	  Buscar();
}
//---------------------------------------------------------------------------
void __fastcall TEliminarComprobante::Button1Click(TObject *Sender)
{
   Query1->Close();
   ClientDataSet1->Active = false;

   Close();
}
//---------------------------------------------------------------------------
void __fastcall TEliminarComprobante::Button3Click(TObject *Sender)
{
   if(ClientDataSet1->Active && !ClientDataSet1->IsEmpty())
   {
	   int idComprobante;
	   if(RG1->ItemIndex == 0)
		  idComprobante = ClientDataSet1->FieldByName("idComprobanteVenta")->AsInteger;
	   else if(RG1->ItemIndex == 1)
		  idComprobante = ClientDataSet1->FieldByName("idComprobanteCompra")->AsInteger;

       Query1->Close();
	   ClientDataSet1->Active = false;

	   if(Application->MessageBox(L"Atención! Se va a eliminar el comprobante seleccionado.",L"Eliminar comprobante?",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES)
	   {
		  if(Application->MessageBox(L"Esta acción no puede deshacerse, realmente desea continuar?",L"Confirma eliminación?",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES)
		  {

			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 if(RG1->ItemIndex == 0)
				AuxQuery->SQL->Add("DELETE FROM ComprobantesVentas WHERE(idComprobanteVenta = :v)");
			 else if(RG1->ItemIndex == 1)
				AuxQuery->SQL->Add("DELETE FROM ComprobantesCompras WHERE(idComprobanteCompra = :v)");

			 AuxQuery->ParamByName("v")->AsInteger = idComprobante;
			 AuxQuery->ExecSQL();
		  }
		  else
			 Buscar();
	   }
	   else
	      Buscar();


   }
}
//---------------------------------------------------------------------------


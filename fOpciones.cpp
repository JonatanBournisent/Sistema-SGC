//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fOpciones.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOpciones *Opciones;
//---------------------------------------------------------------------------
__fastcall TOpciones::TOpciones(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TOpciones::Edit1Change(TObject *Sender)
{
   Query1->Close();
   Query1->SQL->Clear();

   if(llamador == 1)
	  Query1->SQL->Add("SELECT * FROM cuentascompras WHERE(desCuentaCompra LIKE UPPER(:var)) ORDER BY idCuentaCompra");
   else if(llamador == 2)
	  Query1->SQL->Add("SELECT * FROM cuentasventas WHERE(desCuentaVenta LIKE UPPER(:var)) ORDER BY idCuentaVenta");
   else if(llamador == 3)
	  Query1->SQL->Add("SELECT * FROM documentos WHERE(desDocumento LIKE UPPER(:var)) ORDER BY idDocumento");
   else if(llamador == 4)
	  Query1->SQL->Add("SELECT * FROM tipos WHERE(desTipo LIKE UPPER(:var)) ORDER BY idTipo");
   else if(llamador == 5)
	  Query1->SQL->Add("SELECT * FROM jurisdicciones WHERE(desJurisdiccion LIKE UPPER(:var)) ORDER BY idJurisdiccion");
   else if(llamador == 6)
	  Query1->SQL->Add("SELECT * FROM condicionfrenteiva WHERE(desCondicionFrenteIVA LIKE UPPER(:var)) ORDER BY idCondicionFrenteIVA");
   else if(llamador == 7)
	  Query1->SQL->Add("SELECT idContribuyente, razonSocial FROM contribuyentes WHERE(razonSocial LIKE UPPER(:var)) ORDER BY idContribuyente");



   Query1->ParamByName("var")->AsString = "%" + Edit1->Text.UpperCase() + "%";
   Query1->Open();

   ClientDataSet1->Active = false;
   ClientDataSet1->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TOpciones::FormCreate(TObject *Sender)
{
   llamador = 1;
   soloMisClientes = false;
}
//---------------------------------------------------------------------------
void __fastcall TOpciones::FormShow(TObject *Sender)
{
   if(llamador == 1)
   {
	   DBGrid1->Columns->Items[0]->FieldName = "idCuentaCompra";
	   DBGrid1->Columns->Items[1]->FieldName = "desCuentaCompra";
   }
   else if(llamador == 2)
   {
	   DBGrid1->Columns->Items[0]->FieldName = "idCuentaVenta";
	   DBGrid1->Columns->Items[1]->FieldName = "desCuentaVenta";
   }
   else if(llamador == 3)
   {
	   DBGrid1->Columns->Items[0]->FieldName = "idDocumento";
	   DBGrid1->Columns->Items[1]->FieldName = "desDocumento";
   }
   else if(llamador == 4)
   {
	   DBGrid1->Columns->Items[0]->FieldName = "idTipo";
	   DBGrid1->Columns->Items[1]->FieldName = "desTipo";
   }
   else if(llamador == 5)
   {
	   DBGrid1->Columns->Items[0]->FieldName = "idJurisdiccion";
	   DBGrid1->Columns->Items[1]->FieldName = "desJurisdiccion";
   }
   else if(llamador == 6)
   {
	   DBGrid1->Columns->Items[0]->FieldName = "idCondicionFrenteIVA";
	   DBGrid1->Columns->Items[1]->FieldName = "desCondicionFrenteIVA";
   }
   else if(llamador == 7)
   {
	   DBGrid1->Columns->Items[0]->FieldName = "idContribuyente";
	   DBGrid1->Columns->Items[1]->FieldName = "razonSocial";
   }

   Edit1->Clear();

   Query1->Close();
   Query1->SQL->Clear();

   if(llamador == 1)
	  Query1->SQL->Add("SELECT * FROM cuentascompras ORDER BY idCuentaCompra");
   else if(llamador == 2)
	  Query1->SQL->Add("SELECT * FROM cuentasventas ORDER BY idCuentaVenta");
   else if(llamador == 3)
	  Query1->SQL->Add("SELECT * FROM documentos ORDER BY idDocumento");
   else if(llamador == 4)
	  Query1->SQL->Add("SELECT * FROM tipos ORDER BY idTipo");
   else if(llamador == 5)
	  Query1->SQL->Add("SELECT * FROM jurisdicciones ORDER BY idJurisdiccion");
   else if(llamador == 6)
      Query1->SQL->Add("SELECT * FROM condicionfrenteiva ORDER BY idCondicionFrenteIVA");
   else if(llamador == 7)
   {
	  if(soloMisClientes)
		 Query1->SQL->Add("SELECT idContribuyente, razonSocial FROM contribuyentes WHERE esCliente = 1 ORDER BY razonSocial");
	  else
		 Query1->SQL->Add("SELECT idContribuyente, razonSocial FROM contribuyentes ORDER BY razonSocial");
   }

   Query1->Open();

   ClientDataSet1->Active = false;
   ClientDataSet1->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TOpciones::FormClose(TObject *Sender, TCloseAction &Action)
{
   if(!ClientDataSet1->IsEmpty())
   {
	  if(llamador == 1)
		 idRetorno = ClientDataSet1->FieldByName("idCuentaCompra")->AsInteger;
	  if(llamador == 2)
		 idRetorno = ClientDataSet1->FieldByName("idCuentaVenta")->AsInteger;
	  if(llamador == 3)
		 idRetorno = ClientDataSet1->FieldByName("idDocumento")->AsInteger;
	  if(llamador == 4)
		 idRetorno = ClientDataSet1->FieldByName("idTipo")->AsInteger;
	  if(llamador == 5)
		 idRetorno = ClientDataSet1->FieldByName("idJurisdiccion")->AsInteger;
	  if(llamador == 6)
		 idRetorno = ClientDataSet1->FieldByName("idCondicionFrenteIVA")->AsInteger;
	  if(llamador == 7)
		 idRetorno = ClientDataSet1->FieldByName("idContribuyente")->AsInteger;
   }
   else
	  idRetorno = 0;

   soloMisClientes = false;
   Query1->Close();
   ClientDataSet1->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TOpciones::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(Key == VK_ESCAPE || Key == VK_RETURN)
	  Opciones->Close();

   else if(Key == VK_DOWN)
      DBGrid1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TOpciones::Button1Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------



void __fastcall TOpciones::DBGrid1DblClick(TObject *Sender)
{
   Opciones->Close();
}
//---------------------------------------------------------------------------


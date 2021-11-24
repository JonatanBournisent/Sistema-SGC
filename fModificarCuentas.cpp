//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fModificarCuentas.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TModificarCuentas *ModificarCuentas;
//---------------------------------------------------------------------------
__fastcall TModificarCuentas::TModificarCuentas(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TModificarCuentas::RGClick(TObject *Sender)
{
   ClientDataSet1->Active = false;
   Query1->Close();
   Query1->SQL->Clear();

   if(RG->ItemIndex == 0)
   {
	  Query1->SQL->Add("SELECT * FROM cuentasventas ORDER BY idCuentaVenta");

	  DBGrid1->Columns->Items[0]->FieldName = "idCuentaVenta";
	  DBGrid1->Columns->Items[1]->FieldName = "desCuentaVenta";

   }
	else if(RG->ItemIndex == 1)
   {
	  Query1->SQL->Add("SELECT * FROM cuentascompras ORDER BY idCuentaCompra");
	  DBGrid1->Columns->Items[0]->FieldName = "idCuentaCompra";
	  DBGrid1->Columns->Items[1]->FieldName = "desCuentaCompra";
   }

   Query1->Open();
   ClientDataSet1->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TModificarCuentas::Button1Click(TObject *Sender)
{
   if(Edit1->Text == "")
      return;

   if(Application->MessageBox(L"Se va a modificar el registro seleccionado, desea continuar?",L"Modificar registro?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
	  return;

   AuxQuery->Close();
   AuxQuery->SQL->Clear();
   if(RG->ItemIndex == 0)
   {
	  AuxQuery->SQL->Add("UPDATE cuentasventas SET desCuentaVenta = :v WHERE idCuentaVenta = :id");
	  AuxQuery->ParamByName("id")->AsInteger = ClientDataSet1->FieldByName("idCuentaVenta")->AsInteger;
   }
   else if(RG->ItemIndex == 1)
   {
	  AuxQuery->SQL->Add("UPDATE cuentascompras SET desCuentaCompra = :v WHERE idCuentaCompra = :id");
	  AuxQuery->ParamByName("id")->AsInteger = ClientDataSet1->FieldByName("idCuentaCompra")->AsInteger;
   }

   AuxQuery->ParamByName("v")->AsString = Edit1->Text;

   ClientDataSet1->Active = false;
   Query1->Close();

   AuxQuery->ExecSQL();

   Query1->Open();
   ClientDataSet1->Active = true;

   Edit1->Text = "";

}
//---------------------------------------------------------------------------
void __fastcall TModificarCuentas::Button2Click(TObject *Sender)
{
   if(Edit1->Text == "")
      return;

   if(Application->MessageBox(L"Se va a agregar una nueva cuenta, desea continuar?",L"Agregar una cuenta?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
	  return;

   ClientDataSet1->Active = false;
   Query1->Close();

   AuxQuery->Close();
   AuxQuery->SQL->Clear();
   if(RG->ItemIndex == 0)
	  AuxQuery->SQL->Add("INSERT INTO cuentasventas VALUES(NULL, :desc)");
	else if(RG->ItemIndex == 1)
	  AuxQuery->SQL->Add("INSERT INTO cuentascompras VALUES(NULL, :desc)");

   AuxQuery->ParamByName("desc")->AsString = Edit1->Text;
   AuxQuery->ExecSQL();

   Query1->Open();
   ClientDataSet1->Active = true;

   Edit1->Clear();
}
//---------------------------------------------------------------------------




void __fastcall TModificarCuentas::FormShow(TObject *Sender)
{
   Edit1->Clear();

   ClientDataSet1->Active = false;
   Query1->Close();
   Query1->SQL->Clear();

   if(RG->ItemIndex == 0)
   {
	  Query1->SQL->Add("SELECT * FROM cuentasventas ORDER BY idCuentaVenta");

	  DBGrid1->Columns->Items[0]->FieldName = "idCuentaVenta";
	  DBGrid1->Columns->Items[1]->FieldName = "desCuentaVenta";

   }
	else if(RG->ItemIndex == 1)
   {
	  Query1->SQL->Add("SELECT * FROM cuentascompras ORDER BY idCuentaCompra");
	  DBGrid1->Columns->Items[0]->FieldName = "idCuentaCompra";
	  DBGrid1->Columns->Items[1]->FieldName = "desCuentaCompra";
   }

   Query1->Open();
   ClientDataSet1->Active = true;
}
//---------------------------------------------------------------------------


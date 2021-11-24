//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fAsociaciones.h"
#include "fOpciones.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAsociaciones *Asociaciones;
//---------------------------------------------------------------------------
__fastcall TAsociaciones::TAsociaciones(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TAsociaciones::VerificarDatos(TObject *Sender)
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

		  if(asocOK && contOK)
		  {
			 AuxQuery->SQL->Clear();

			 if(llamador == 1)
				AuxQuery->SQL->Add("SELECT refCuentaVenta FROM asociacionclientes WHERE(refContribuyente = :v1 AND refCliente = :v2)");
             else if(llamador == 2)
				AuxQuery->SQL->Add("SELECT refCuentaCompra FROM asociacionproveedores WHERE(refContribuyente = :v1 AND refProveedor = :v2)");

			 AuxQuery->ParamByName("v1")->AsString = idContribuyente;
			 AuxQuery->ParamByName("v2")->AsString = idAsociado;
			 AuxQuery->Open();

			 if(llamador == 1)
				EdCuenta->Text = AuxQuery->FieldByName("refCuentaVenta")->AsString;
			 else if(llamador == 2)
				EdCuenta->Text = AuxQuery->FieldByName("refCuentaCompra")->AsString;

			 AuxQuery->Close();

			 VerificarDatos(EdCuenta);
		  }
	  }
	  else if(Sender == EdAsociado)
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
				desAsociado->Caption = AuxQuery->FieldByName("razonSocial")->AsString;
				idAsociado = AuxQuery->FieldByName("idContribuyente")->AsInteger;
				Edit->Color = clWindow;
				asocOK = true;
			 }
			 else
			 {
				desAsociado->Caption = "Cliente desconocido";
				idAsociado = 0;
				Edit->Color = clWebLightCoral;
				asocOK = false;
			 }
		  }
		  else
		  {
			 desAsociado->Caption = "";
			 Edit->Color = clWebLightCoral;
			 idAsociado = 0;
			 asocOK = false;
		  }
		  AuxQuery->Close();

		  if(asocOK && contOK)
		  {
			 AuxQuery->SQL->Clear();

			 if(llamador == 1)
				AuxQuery->SQL->Add("SELECT refCuentaVenta FROM asociacionclientes WHERE(refContribuyente = :v1 AND refCliente = :v2)");
			 else if(llamador == 2)
				AuxQuery->SQL->Add("SELECT refCuentaCompra FROM asociacionproveedores WHERE(refContribuyente = :v1 AND refProveedor = :v2)");

			 AuxQuery->ParamByName("v1")->AsString = idContribuyente;
			 AuxQuery->ParamByName("v2")->AsString = idAsociado;
			 AuxQuery->Open();

			 if(llamador == 1)
				EdCuenta->Text = AuxQuery->FieldByName("refCuentaVenta")->AsString;
			 else if(llamador == 2)
				EdCuenta->Text = AuxQuery->FieldByName("refCuentaCompra")->AsString;

			 AuxQuery->Close();

			 VerificarDatos(EdCuenta);
		  }
	  }
	  else if(Sender == EdCuenta)
	  {
		  if(Edit->Text != "")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 if(llamador == 1)
				AuxQuery->SQL->Add("SELECT desCuentaVenta FROM cuentasventas WHERE(idCuentaVenta = :v)");
			 else if(llamador == 2)
                AuxQuery->SQL->Add("SELECT desCuentaCompra FROM cuentascompras WHERE(idCuentaCompra = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				if(llamador == 1)
				   desCuenta->Caption = AuxQuery->FieldByName("desCuentaVenta")->AsString;
				else if(llamador == 2)
				   desCuenta->Caption = AuxQuery->FieldByName("desCuentaCompra")->AsString;
				Edit->Color = clWindow;
				ccOK = true;
			 }
			 else
			 {
				desCuenta->Caption = "No existe el indicador de cuenta";
				Edit->Color = clWebLightCoral;
				ccOK = false;
			 }
		  }
		  else
		  {
			 desCuenta->Caption = "";
			 Edit->Color = clWebLightCoral;
			 ccOK = false;
		  }
		  AuxQuery->Close();
	  }
   }
   else
	  ShowMessage("ERROR: El *Sender no es una clase TEdit");
}

//---------------------------------------------------------------------------

void TAsociaciones::RestablecerFormulario(void)
{
   ccOK = false;
   asocOK = false;
   contOK = false ;

   EdCuenta->Text = "";
   desCuenta->Caption = "-";
   desContribuyente->Caption = "-";
   desAsociado->Caption = "-";
   EdContribuyente->Text = "__-________-_";
   EdAsociado->Text = "__-________-_";

   EdContribuyente->Color = clWindow;
   EdAsociado->Color = clWindow;
   EdCuenta->Color = clWindow;


   if(llamador == 1)
   {
	  Label5->Caption = "CUIT del cliente";
	  Label7->Caption = "Cuenta venta asociada";
   }
   else if(llamador == 2)
   {
      Label5->Caption = "CUIT del proveedor";
	  Label7->Caption = "Cuenta compra asociada";
   }

   EdContribuyente->SetFocus();
}

//---------------------------------------------------------------------------

void __fastcall TAsociaciones::EdContribuyenteKeyDown(TObject *Sender, WORD &Key,
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
void __fastcall TAsociaciones::EdContribuyenteKeyPress(TObject *Sender, System::WideChar &Key)

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

	  EdAsociado->SetFocus();
   }

   EdContribuyente->SelLength = 1;
}
//---------------------------------------------------------------------------
void __fastcall TAsociaciones::EdContribuyenteKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(EdContribuyente->SelStart == 2 || EdContribuyente->SelStart == 11)
	  EdContribuyente->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TAsociaciones::EdAsociadoKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(EdAsociado->SelStart == 2 || EdAsociado->SelStart == 11)
	  EdAsociado->SelStart++;
}
//---------------------------------------------------------------------------
void __fastcall TAsociaciones::EdAsociadoKeyPress(TObject *Sender, System::WideChar &Key)

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
	  EdAsociado->Text = AuxQuery->FieldByName("cuit")->AsString;
	  AuxQuery->Close();

	  if(EdAsociado->Text == "")
		 EdAsociado->Text = "__-________-_";

	  EdCuenta->SetFocus();
   }

   EdAsociado->SelLength = 1;
}
//---------------------------------------------------------------------------
void __fastcall TAsociaciones::EdAsociadoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(Key == VK_BACK)
   {
	  Key = NULL;
	  EdAsociado->Text = "___-________-_";
	  EdAsociado->SelStart = 0;
   }
   else if(Key == VK_DELETE)
   {
	  Key = NULL;
	  EdAsociado->Text = "__-________-_";
	  EdAsociado->SelStart = 0;
   }
}
//---------------------------------------------------------------------------

void __fastcall TAsociaciones::EdContribuyenteMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   if(EdContribuyente->SelStart == 2 || EdContribuyente->SelStart == 11)
	  EdContribuyente->SelStart++;
}
//---------------------------------------------------------------------------
void __fastcall TAsociaciones::EdAsociadoMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   if(EdAsociado->SelStart == 2 || EdAsociado->SelStart == 11)
	  EdAsociado->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TAsociaciones::EdContribuyenteExit(TObject *Sender)
{
   VerificarDatos(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TAsociaciones::EdAsociadoExit(TObject *Sender)
{
   VerificarDatos(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TAsociaciones::EdCuentaKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
	  if(llamador == 1)
		 Opciones->llamador = 2;
	  else if (llamador == 2)
		 Opciones->llamador = 1;

	  Opciones->ShowModal();
	  Key = NULL;
	  EdCuenta->Text = IntToStr(Opciones->idRetorno);
   }
}
//---------------------------------------------------------------------------

void __fastcall TAsociaciones::EdCuentaExit(TObject *Sender)
{
   VerificarDatos(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TAsociaciones::FormShow(TObject *Sender)
{
   RestablecerFormulario();
}
//---------------------------------------------------------------------------
void __fastcall TAsociaciones::BtnGuardarClick(TObject *Sender)
{
   if(asocOK && contOK)
   {
      AuxQuery->Close();
	  AuxQuery->SQL->Clear();

	  if(llamador == 1)
		 AuxQuery->SQL->Add("SELECT idAsociacionCliente FROM asociacionclientes WHERE(refContribuyente = :v1 AND refCliente = :v2)");
	  else if(llamador == 2)
		 AuxQuery->SQL->Add("SELECT idAsociacionProveedor FROM asociacionproveedores WHERE(refContribuyente = :v1 AND refProveedor = :v2)");

	  AuxQuery->ParamByName("v1")->AsString = idContribuyente;
	  AuxQuery->ParamByName("v2")->AsString = idAsociado;
	  AuxQuery->Open();

	  bool modificando;
	  int id;
	  if(!AuxQuery->IsEmpty())
	  {
		 modificando = true;
		 if(llamador == 1)
			id = AuxQuery->FieldByName("idAsociacionCliente")->AsInteger;
		 else if(llamador == 2)
			id = AuxQuery->FieldByName("idAsociacionProveedor")->AsInteger;
	  }
	  else
		 modificando = false;

	  AuxQuery->Close();

      if(modificando)
	  {
		 if(Application->MessageBox(L"Se va a guardar la modificación realizada, desea continuar?",L"Guardar datos?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
			return;

		 Query1->Close();
		 Query1->SQL->Clear();

		 if(llamador == 1)
			Query1->SQL->Add("UPDATE asociacionclientes SET refContribuyente = :v1, refCliente = :v2, refCuentaVenta = :v3 WHERE (idAsociacionCliente = :id)");
		 else if(llamador == 2)
			Query1->SQL->Add("UPDATE asociacionproveedores SET refContribuyente = :v1, refProveedor = :v2, refCuentaCompra = :v3 WHERE (idAsociacionProveedor = :id)");

		 Query1->ParamByName("id")->AsInteger = id;
		 Query1->ParamByName("v1")->AsInteger = idContribuyente;
		 Query1->ParamByName("v2")->AsInteger = idAsociado;
		 Query1->ParamByName("v3")->AsString = EdCuenta->Text;

		 Query1->ExecSQL();

	  }
	  else if(!modificando)
	  {
		 if(Application->MessageBox(L"Se va a agregar una nueva asociación por defecto, desea continuar?",L"Guardar datos?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
			return;

		 Query1->Close();
		 Query1->SQL->Clear();

		 if(llamador == 1)
			Query1->SQL->Add("INSERT INTO asociacionclientes VALUES(NULL, :v1, :v2, :v3)");
		 else if(llamador == 2)
			Query1->SQL->Add("INSERT INTO asociacionproveedores VALUES(NULL, :v1, :v2, :v3)");

		 Query1->ParamByName("v1")->AsInteger = idContribuyente;
		 Query1->ParamByName("v2")->AsInteger = idAsociado;
		 Query1->ParamByName("v3")->AsString = EdCuenta->Text;

		 Query1->ExecSQL();
	  }
	  RestablecerFormulario();
   }
   else
   {
	  Application->MessageBox(L"Hay errores en los datos ingresados.\nPor favor revise los casilleros resaltados",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  return;
   }
}
//---------------------------------------------------------------------------
void __fastcall TAsociaciones::BtnCancelarClick(TObject *Sender)
{
   RestablecerFormulario();
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TAsociaciones::RGClick(TObject *Sender)
{
   if(RG->ItemIndex == 0)
	  llamador = 1;
   else if(RG->ItemIndex == 1)
	  llamador = 2;

   RestablecerFormulario();
}
//---------------------------------------------------------------------------


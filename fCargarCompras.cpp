//---------------------------------------------------------------------------

#include <vcl.h>
#include <dateUtils.hpp>
#pragma hdrstop

#include "fCargarCompras.h"
#include "fOpciones.h"
#include "fAgregarContribuyente.h"
#include "uMostrarComprobantes.h"
#include "fModificarCuentas.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCargarCompras *CargarCompras;
//---------------------------------------------------------------------------
__fastcall TCargarCompras::TCargarCompras(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

//***************************************************************************
//***************INICIO DE DEFINICION DE FUNCIONES***************************
//***************************************************************************

//---------------------------------------------------------------------------

void TCargarCompras::LimpiarEdit(TObject *Sender)
{
   if(dynamic_cast <TEdit *>(Sender) != NULL)
   {
	  TEdit *Edit = dynamic_cast <TEdit *>(Sender);
	  Edit->Text = Edit->Text.SubString(3,Edit->Text.Length()-2);
	  Edit->SelectAll();
   }
}
//---------------------------------------------------------------------------

void TCargarCompras::DarFormatoEdit(TObject *Sender)
{
   if(dynamic_cast <TEdit *>(Sender) != NULL)
   {
	  TEdit *Edit = dynamic_cast <TEdit *>(Sender);
	  if(Edit->Text == "")
		 Edit->Text = "0";
	  else if(Edit->Text.Pos("-"))
	     Edit->Text = Edit->Text.Delete(Edit->Text.Pos("-"),1);
	  Edit->Text = FormatFloat("$ 0.#0", StrToFloat(Edit->Text));
   }
}
//---------------------------------------------------------------------------

void TCargarCompras::CalcularIVA(TObject *Sender)
{
   if(dynamic_cast <TEdit *>(Sender) != NULL)
   {
	  TEdit *Edit = dynamic_cast <TEdit *>(Sender);

	  if(Sender == EdNetoGravado1 && al1OK)
	  {
		 IVA1 = StrToFloat(Edit->Text.SubString(3,Edit->Text.Length()-2)) * ali1 / 100.0;
		 LabIVA1->Caption = FormatFloat("$ 0.#0", IVA1);
	  }

	  else if(Sender == EdNetoGravado2 && al2OK)
	  {
		 IVA2 = StrToFloat(Edit->Text.SubString(3,Edit->Text.Length()-2)) * ali2 / 100.0;
		 LabIVA2->Caption = FormatFloat("$ 0.#0", IVA2);
	  }

	  else if(Sender == EdNetoGravado3 && al3OK)
	  {
		 IVA3 = StrToFloat(Edit->Text.SubString(3,Edit->Text.Length()-2)) * ali3 / 100.0;
		 LabIVA3->Caption = FormatFloat("$ 0.#0", IVA3);
	  }

	  else if(Sender == EdNetoGravado4 && al4OK)
	  {
		 IVA4 = StrToFloat(Edit->Text.SubString(3,Edit->Text.Length()-2)) * ali4 / 100.0;
		 LabIVA4->Caption = FormatFloat("$ 0.#0", IVA4);
	  }

	  if(!al1OK)
		 LabIVA1->Caption = "-";

	  if(!al2OK)
		 LabIVA2->Caption = "-";

	  if(!al3OK)
		 LabIVA3->Caption = "-";

	  if(!al4OK)
		 LabIVA4->Caption = "-";
   }
}
//---------------------------------------------------------------------------

void TCargarCompras::DarFormatoEntrada(System::WideChar &Key)
{
   if(Key == '.')
	  Key = FormatSettings.DecimalSeparator;
   else if((Key > '9' || Key < '0') && Key != '\b')
	  Key = NULL;
}
//---------------------------------------------------------------------------

void TCargarCompras::SeleccionarTodo(TObject *Sender)
{
   if(dynamic_cast <TEdit *>(Sender) != NULL)
   {
	  TEdit *Edit = dynamic_cast <TEdit *>(Sender);
	  Edit->SelectAll();
   }
}
//---------------------------------------------------------------------------

void TCargarCompras::VerificarDatos(TObject *Sender)
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
			 AuxQuery->SQL->Add("SELECT idContribuyente, razonSocial, refJurisdiccion, refCondicionFrenteIVA FROM Contribuyentes WHERE(cuit = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				desContribuyente->Caption = AuxQuery->FieldByName("razonSocial")->AsString;
				idContribuyente = AuxQuery->FieldByName("idContribuyente")->AsInteger;
                Edit1->Text = IntToStr(idContribuyente);
				EdJurisdiccion->Text = AuxQuery->FieldByName("refJurisdiccion")->AsInteger;
				civaCont = AuxQuery->FieldByName("refCondicionFrenteIVA")->AsInteger;
				Edit->Color = clWindow;
				contOK = true;
			 }
			 else
			 {
				desContribuyente->Caption = "Contribuyente desconocido";
				idContribuyente = 0;
				Edit1->Text = "";
				EdJurisdiccion->Text = "";
				Edit->Color = clWebLightCoral;
				contOK = false;
			 }
		  }
		  else
		  {
			 desContribuyente->Caption = "";
			 Edit->Color = clWebLightCoral;
			 idContribuyente = 0;
			 Edit1->Text = "";
			 EdJurisdiccion->Text = "";
			 contOK = false;
		  }
		  AuxQuery->Close();

		  VerificarDatos(EdJurisdiccion);

		  if(provOK && contOK)
		  {
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT refCuentaCompra FROM asociacionproveedores WHERE(refContribuyente = :v1 AND refProveedor = :v2)");
			 AuxQuery->ParamByName("v1")->AsString = idContribuyente;
			 AuxQuery->ParamByName("v2")->AsString = idProveedor;
			 AuxQuery->Open();
			 EdCuentaCompra->Text = AuxQuery->FieldByName("refCuentaCompra")->AsString;
			 AuxQuery->Close();

			 VerificarDatos(EdCuentaCompra);
		  }
	  }
	  else if(Sender == EdProveedor)
	  {
		  if(Edit->Text != "__-________-_")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT idContribuyente, razonSocial, refCondicionFrenteIVA FROM Contribuyentes WHERE(cuit = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				desProveedor->Caption = AuxQuery->FieldByName("razonSocial")->AsString;
				idProveedor = AuxQuery->FieldByName("idContribuyente")->AsInteger;
				Edit2->Text = IntToStr(idProveedor);
				civaProv = AuxQuery->FieldByName("refCondicionFrenteIVA")->AsInteger;
				Edit->Color = clWindow;
				provOK = true;
			 }
			 else
			 {
				desProveedor->Caption = "Proveedor desconocido";
				idProveedor = 0;
				Edit2->Text = "";
				Edit->Color = clWebLightCoral;
				provOK = false;
			 }

			 if(!provOK && Edit->Text.Pos("_") == 0)
				AgProveedor->Enabled = true;
			 else
				AgProveedor->Enabled = false;
		  }
		  else
		  {
			 desProveedor->Caption = "";
			 Edit->Color = clWebLightCoral;
			 idProveedor = 0;
			 Edit2->Text = "";
			 provOK = false;
			 AgProveedor->Enabled = false;
		  }
		  AuxQuery->Close();

		  if(provOK && contOK)
		  {
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT refCuentaCompra FROM asociacionproveedores WHERE(refContribuyente = :v1 AND refProveedor = :v2)");
			 AuxQuery->ParamByName("v1")->AsString = idContribuyente;
			 AuxQuery->ParamByName("v2")->AsString = idProveedor;
			 AuxQuery->Open();
			 EdCuentaCompra->Text = AuxQuery->FieldByName("refCuentaCompra")->AsString;
			 AuxQuery->Close();

			 VerificarDatos(EdCuentaCompra);
		  }
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
			 else if(fechOK && ((StrToInt(EdFecha->Text.SubString(7,4)) > StrToInt(Edit->Text.SubString(4,4))) ||
					((StrToInt(EdFecha->Text.SubString(7,4)) <= StrToInt(Edit->Text.SubString(4,4))) &&
					(StrToInt(EdFecha->Text.SubString(4,2)) > StrToInt(Edit->Text.SubString(1,2))))))
			 {

				Edit->Color = clWebLightCoral;
				Edit->Hint = "El período ingresado es inferior a la fecha";
				Edit->ShowHint = true;
				fechOK = false;
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
			 else if(perOK && ((StrToInt(Edit->Text.SubString(7,4)) > StrToInt(EdPeriodo->Text.SubString(4,4))) ||
					((StrToInt(Edit->Text.SubString(7,4)) <= StrToInt(EdPeriodo->Text.SubString(4,4))) &&
					(StrToInt(Edit->Text.SubString(4,2)) > StrToInt(EdPeriodo->Text.SubString(1,2))))))
			 {

				Edit->Color = clWebLightCoral;
				Edit->Hint = "La fecha ingresada es posterior al período";
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
	  else if(Sender == EdCuentaCompra)
	  {
		  if(Edit->Text != "")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT desCuentaCompra FROM cuentascompras WHERE(idCuentaCompra = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				desCuentaCompra->Caption = AuxQuery->FieldByName("desCuentaCompra")->AsString;
				Edit->Color = clWindow;
				ccOK = true;
			 }
			 else
			 {
				desCuentaCompra->Caption = "No existe el indicador de cuenta";
				Edit->Color = clWebLightCoral;
				ccOK = false;
			 }
		  }
		  else
		  {
			 desCuentaCompra->Caption = "";
			 Edit->Color = clWebLightCoral;
			 ccOK = false;
		  }
		  AuxQuery->Close();
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
	  else if(Sender == EdJurisdiccion)
	  {
		  if(Edit->Text != "")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT desJurisdiccion FROM jurisdicciones WHERE(idJurisdiccion = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				desJurisdiccion->Caption = AuxQuery->FieldByName("desJurisdiccion")->AsString;
				Edit->Color = clWindow;
				juriOK = true;
			 }
			 else
			 {
				desJurisdiccion->Caption = "No existe el indicador de jurisdiccion";
				Edit->Color = clWebLightCoral;
				juriOK = false;
			 }
		  }
		  else
		  {
			 desJurisdiccion->Caption = "";
			 Edit->Color = clWebLightCoral;
			 juriOK = false;
		  }
		  AuxQuery->Close();
	  }
	  else if(Sender == EdAlicuota1 || Sender == EdAlicuota2 || Sender == EdAlicuota3 || Sender == EdAlicuota4)
	  {
		  if(Edit->Text != "")
		  {
			 AuxQuery->Close();
			 AuxQuery->SQL->Clear();
			 AuxQuery->SQL->Add("SELECT valor FROM alicuotas WHERE(idAlicuota = :v)");
			 AuxQuery->ParamByName("v")->AsString = Edit->Text;
			 AuxQuery->Open();
			 if(!AuxQuery->IsEmpty())
			 {
				if(Sender == EdAlicuota1)
				{
				   desAlicuota1->Caption = AuxQuery->FieldByName("valor")->AsString + "%";
				   ali1 = AuxQuery->FieldByName("valor")->AsFloat;
				   al1OK = true;
				}

				else if(Sender == EdAlicuota2)
				{
				   desAlicuota2->Caption = AuxQuery->FieldByName("valor")->AsString + "%";
				   ali2 = AuxQuery->FieldByName("valor")->AsFloat;
				   al2OK = true;
				}

				else if(Sender == EdAlicuota3)
				{
				   desAlicuota3->Caption = AuxQuery->FieldByName("valor")->AsString + "%";
				   ali3 = AuxQuery->FieldByName("valor")->AsFloat;
				   al3OK = true;
				}

				else if(Sender == EdAlicuota4)
				{
				   desAlicuota4->Caption = AuxQuery->FieldByName("valor")->AsString + "%";
				   ali4 = AuxQuery->FieldByName("valor")->AsFloat;
				   al4OK = true;
				}

				Edit->Color = clWindow;

			 }
			 else
			 {
				if(Sender == EdAlicuota1)
				{
				   desAlicuota1->Caption = "X";
				   ali1 = 0.0;
				   al1OK = false;
				}
				else if(Sender == EdAlicuota2)
				{
				   desAlicuota2->Caption = "X";
				   ali2 = 0.0;
				   al2OK = false;
				}
				else if(Sender == EdAlicuota3)
				{
				   desAlicuota3->Caption = "X";
				   ali3 = 0.0;
				   al3OK = false;
				}
				else if(Sender == EdAlicuota4)
				{
				   desAlicuota4->Caption = "X";
				   ali4 = 0.0;
				   al4OK = false;
				}

				Edit->Color = clWebLightCoral;
			 }
		  }
		  else
		  {
			 if(Sender == EdAlicuota1)
			 {
				desAlicuota1->Caption = "";
				ali1 = 0.0;
				al1OK = false;
			 }
			 else if(Sender == EdAlicuota2)
			 {
				desAlicuota2->Caption = "";
				ali2 = 0.0;
				al2OK = false;
			 }
			 else if(Sender == EdAlicuota3)
			 {
				desAlicuota3->Caption = "";
				ali3 = 0.0;
				al3OK = false;
			 }
			 else if(Sender == EdAlicuota4)
			 {
				desAlicuota4->Caption = "";
				ali4 = 0.0;
				al4OK = false;
			 }

			 Edit->Color = clWebLightCoral;
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

void TCargarCompras::ActualizarTotal(void)
{
   float total = StrToFloat(EdNetoGravado1->Text.SubString(3,EdNetoGravado1->Text.Length()-2));
   total = total + StrToFloat(EdNetoGravado2->Text.SubString(3,EdNetoGravado2->Text.Length()-2));
   total = total + StrToFloat(EdNetoGravado3->Text.SubString(3,EdNetoGravado3->Text.Length()-2));
   total = total + StrToFloat(EdNetoGravado4->Text.SubString(3,EdNetoGravado4->Text.Length()-2));
   total = total + StrToFloat(EdRetencionesIVA->Text.SubString(3,EdRetencionesIVA->Text.Length()-2));
   total = total + StrToFloat(EdPercepcionesIVA->Text.SubString(3,EdPercepcionesIVA->Text.Length()-2));
   total = total + StrToFloat(EdRetencionesIB->Text.SubString(3,EdRetencionesIB->Text.Length()-2));
   total = total + StrToFloat(EdPercepcionesIB->Text.SubString(3,EdPercepcionesIB->Text.Length()-2));
   total = total + StrToFloat(EdRetencionesGanancias->Text.SubString(3,EdRetencionesGanancias->Text.Length()-2));
   total = total + StrToFloat(EdConcNoGravados->Text.SubString(3,EdConcNoGravados->Text.Length()-2));
   total = total + StrToFloat(EdExentos->Text.SubString(3,EdExentos->Text.Length()-2));

   total = total + IVA1 + IVA2 + IVA3 + IVA4;

   EdTotal->Text = FormatFloat("$ 0.#0", total);
}
//---------------------------------------------------------------------------

int TCargarCompras::YaExiste(void) //Si ya existe el comprobante retorna el idComprobanteCompra, si no, retorna 0
{
   // Ya existe el mismo comprobante?

   if(EdProveedor->Text == "__-________-_" || EdPtoVenta->Text == "00000" || EdNroComprobante->Text == "00000000")
	  return 0;
   if(EdDocumento->Text == "" || EdTipo->Text == "")
	  return 0;

   AuxQuery->Close();
   AuxQuery->SQL->Clear();
   AuxQuery->SQL->Add("SELECT idContribuyente FROM contribuyentes WHERE(cuit = :v)");
   AuxQuery->ParamByName("v")->AsString = EdProveedor->Text;
   AuxQuery->Open();
   if(!AuxQuery->IsEmpty())
   {
	  int refProveedor = AuxQuery->FieldByName("idContribuyente")->AsInteger;

	  AuxQuery->Close();
	  AuxQuery->SQL->Clear();
	  AuxQuery->SQL->Add("SELECT idComprobanteCompra FROM comprobantescompras WHERE(refProveedor = :v1 AND ptoVenta = :v2 AND nroComprobante = :v3 AND refDocumento = :v4 AND refTipo = :v5)");
	  AuxQuery->ParamByName("v1")->AsInteger = refProveedor;
	  AuxQuery->ParamByName("v2")->AsString = EdPtoVenta->Text;
	  AuxQuery->ParamByName("v3")->AsString = EdNroComprobante->Text;
	  AuxQuery->ParamByName("v4")->AsString = EdDocumento->Text;
	  AuxQuery->ParamByName("v5")->AsString = EdTipo->Text;
	  AuxQuery->Open();
	  if(AuxQuery->IsEmpty())
	  {
		 AuxQuery->Close();
		 return 0;
	  }
	  int id = AuxQuery->FieldByName("idComprobanteCompra")->AsInteger;
	  AuxQuery->Close();
	  return id;
   }
   AuxQuery->Close();
   return 0;
}
//---------------------------------------------------------------------------

void TCargarCompras::TraerDatos(int idCompCompra)
{
    AuxQuery->Close();
	AuxQuery->SQL->Clear();
	AuxQuery->SQL->Add("SELECT * FROM comprobantescompras WHERE(idComprobanteCompra = :v)");
	AuxQuery->ParamByName("v")->AsInteger = idCompCompra;
	AuxQuery->Open();

	EdAlicuota1->Text = AuxQuery->FieldByName("refAlicuota1")->AsString;
	EdAlicuota2->Text = AuxQuery->FieldByName("refAlicuota2")->AsString;
	EdAlicuota3->Text = AuxQuery->FieldByName("refAlicuota3")->AsString;
	EdAlicuota4->Text = AuxQuery->FieldByName("refAlicuota4")->AsString;

	EdPeriodo->Text = FormatDateTime("mm/yyyy", AuxQuery->FieldByName("fechaPeriodo")->AsDateTime);
	EdFecha->Text = FormatDateTime("dd/mm/yyyy", AuxQuery->FieldByName("fechaComprobante")->AsDateTime);

	EdCuentaCompra->Text = AuxQuery->FieldByName("refCuentaCompra")->AsString;
	EdJurisdiccion->Text = AuxQuery->FieldByName("refJurisdiccion")->AsString;

	EdNetoGravado1->Text = AuxQuery->FieldByName("netoGravado1")->AsString;
	DarFormatoEdit(EdNetoGravado1);
	EdNetoGravado2->Text = AuxQuery->FieldByName("netoGravado2")->AsString;
	DarFormatoEdit(EdNetoGravado2);
	EdNetoGravado3->Text = AuxQuery->FieldByName("netoGravado3")->AsString;
	DarFormatoEdit(EdNetoGravado3);
	EdNetoGravado4->Text = AuxQuery->FieldByName("netoGravado4")->AsString;
	DarFormatoEdit(EdNetoGravado4);
	EdRetencionesIVA->Text = AuxQuery->FieldByName("retencionesIVA")->AsString;
	DarFormatoEdit(EdRetencionesIVA);
	EdPercepcionesIVA->Text = AuxQuery->FieldByName("percepcionesIVA")->AsString;
	DarFormatoEdit(EdPercepcionesIVA);
	EdRetencionesIB->Text = AuxQuery->FieldByName("retencionesIB")->AsString;
	DarFormatoEdit(EdRetencionesIB);
	EdPercepcionesIB->Text = AuxQuery->FieldByName("percepcionesIB")->AsString;
	DarFormatoEdit(EdPercepcionesIB);
	EdRetencionesGanancias->Text = AuxQuery->FieldByName("retencionesGanancias")->AsString;
	DarFormatoEdit(EdRetencionesGanancias);
	EdConcNoGravados->Text = AuxQuery->FieldByName("conceptosNoGravados")->AsString;
	DarFormatoEdit(EdConcNoGravados);
	EdExentos->Text = AuxQuery->FieldByName("exentos")->AsString;
	DarFormatoEdit(EdExentos);
	EdTotal->Text = AuxQuery->FieldByName("total")->AsString;
	DarFormatoEdit(EdTotal);

	AuxQuery->Close();

	VerificarDatos(EdCuentaCompra);
	VerificarDatos(EdAlicuota1);
	VerificarDatos(EdAlicuota2);
	VerificarDatos(EdAlicuota3);
	VerificarDatos(EdAlicuota4);

	VerificarDatos(EdPeriodo);
	VerificarDatos(EdFecha);
	VerificarDatos(EdJurisdiccion);

	CalcularIVA(EdNetoGravado1);
	CalcularIVA(EdNetoGravado2);
	CalcularIVA(EdNetoGravado3);
	CalcularIVA(EdNetoGravado4);
}
//---------------------------------------------------------------------------

void TCargarCompras::RestablecerFormulario(void)
{
	EdContribuyente->Text = "__-________-_";
	EdContribuyente->Color = clWindow;
	EdProveedor->Text = "__-________-_";
	EdProveedor->Color = clWindow;
	EdPeriodo->Text = "__/____";
	EdPeriodo->Color = clWindow;
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
	EdJurisdiccion->Text = "";
    EdJurisdiccion->Color = clWindow;
	EdAlicuota1->Text = 1;
	EdAlicuota2->Text = 2;
	EdAlicuota3->Text = 3;
	EdAlicuota4->Text = 4;
	EdCuentaCompra->Text = "";
	EdCuentaCompra->Color = clWindow;
	EdNetoGravado1->Text = "$ 0,00";
	EdNetoGravado2->Text = "$ 0,00";
	EdNetoGravado3->Text = "$ 0,00";
	EdNetoGravado4->Text = "$ 0,00";
	EdRetencionesIVA->Text = "$ 0,00";
	EdPercepcionesIVA->Text = "$ 0,00";
	EdRetencionesIB->Text = "$ 0,00";
	EdPercepcionesIB->Text = "$ 0,00";
	EdRetencionesGanancias->Text = "$ 0,00";
	EdConcNoGravados->Text = "$ 0,00";
	EdExentos->Text = "$ 0,00";
	EdTotal->Text = "$ 0,00";

	Edit1->Text = "";
	Edit2->Text = "";

	desContribuyente->Caption = "-";
	desProveedor->Caption = "-";
	desCuentaCompra->Caption = "-";
	desDocumento->Caption = "-";
	desTipo->Caption = "-";
	desAlicuota1->Caption = "21%";
	desAlicuota2->Caption = "10,5%";
	desAlicuota3->Caption = "27%";
	desAlicuota4->Caption = "0,0%";

	modificando = false;
	idModificado = 0;
	idContribuyente = 0;
	idProveedor = 0;
	CargarCompras->Caption = "Cargar comprobantes de compras";
	BtnAgregarComp->Caption = "Guardar";
	BtnAgregarYCont->Caption = "Guardar y cargar otro";
	btEliminarComp->Enabled = false;

	contOK = false;
	perOK = false;
	fechOK = false;
	provOK = false;
	ptoOK = false;
	nroOK = false;
	ccOK = false;
	tipoOK = false;
	docOK = false;
	juriOK = false;
	al1OK = true;
	al2OK = true;
	al3OK = true;
	al4OK = true;
	AgProveedor->Enabled = false;

	IVA1 = 0.0;
	IVA2 = 0.0;
	IVA3 = 0.0;
	IVA4 = 0.0;

	ali1 = 21.0;
	ali2 = 10.5;
	ali3 = 27.0;
	ali4 = 0.0;

	LabIVA1->Caption = "$ 0,00";
	LabIVA2->Caption = "$ 0,00";
	LabIVA3->Caption = "$ 0,00";
	LabIVA4->Caption = "$ 0,00";

	EdContribuyente->SetFocus();
}
//---------------------------------------------------------------------------

void TCargarCompras::RestablecerFormularioCont(void)
{
	AnsiString s1 = EdContribuyente->Text;
	AnsiString s2 = EdPeriodo->Text;
	AnsiString s3 = EdProveedor->Text;

	RestablecerFormulario();

	EdContribuyente->Text = s1;
	EdPeriodo->Text = s2;
	EdProveedor->Text = s3;
	VerificarDatos(EdContribuyente);
	VerificarDatos(EdPeriodo);
	VerificarDatos(EdProveedor);
}
//---------------------------------------------------------------------------

AnsiString TCargarCompras::LimpiarNumero(AnsiString s)
{
	AnsiString aux;
	aux = s.SubString(3,s.Length());
	aux = aux.Delete(aux.Length()-2,1);
	aux = aux.Insert(".", aux.Length()-1);
    return aux;
}
//---------------------------------------------------------------------------

bool TCargarCompras::GuardarDatos(void)
{
   if(!(contOK && perOK && fechOK && provOK && ptoOK && nroOK && ccOK && tipoOK && docOK && juriOK && al1OK && al2OK && al3OK && al4OK))
   {
	  Application->MessageBox(L"Hay errores en los datos ingresados.\nPor favor revise los casilleros resaltados",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  return false;
   }

   if(idContribuyente == idProveedor)
   {
	  Application->MessageBox(L"No pueden coincidir los cuits del informante y el proveedor",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	  return false;
   }

   if(EdTipo->Text == "1")
   {
	  if(civaCont != 2 || civaProv != 2)
	  {
		 Application->MessageBox(L"Un comprobante A solo puede ser emitido y/o recibido por responsables inscriptos",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		 return false;
	  }
   }

   if(EdTipo->Text == "3")
   {
	  if(civaProv != 1 && civaProv != 4)
	  {
		 Application->MessageBox(L"Un comprobante C solo puede ser emitido por monotributistas o exentos",L"No se realizaron cambios",MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
		 return false;
	  }
   }


   if(Application->MessageBox(L"Se va a guardar la información ingresada, desea continuar?",L"Guardar datos?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
	  return false;

   if(modificando)
	  if(Application->MessageBox(L"Se van a modificar los datos de un comprobante previamente cargado\n\nREALMENTE DESEA CONTINUAR?",L"ATENCIÓN!",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
		 return false;

   if(EdTotal->Text == "$ 0,00")
	  if(Application->MessageBox(L"Se va a cargar un comprobante con total $ 0,00, es correcto?",L"ATENCIÓN!",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
		 return false;

   //si contOK y provOK -> idContribuyente e idProveedor contienen datos correctos

   AnsiString s;

   SQLQuery1->Close();
   SQLQuery1->SQL->Clear();

   if(!modificando)
   {
	  SQLQuery1->SQL->Add("INSERT INTO comprobantescompras VALUES (NULL, :v1, :v2, :v3, :v4, :v5, :v6, :v7, :v8, :v9, :v10, :v11, :v12, :v13, :v14, :v15, :v16, :v17, :v18, :v19, :v20, :v21, :v22, :v23, :v24, :v25, :v26)");
   }
   else
   {
	  SQLQuery1->SQL->Add("UPDATE comprobantescompras SET fechaPeriodo = :v1, fechaComprobante = :v2, ptoVenta = :v3, nroComprobante = :v4, refProveedor = :v5, refDocumento = :v6, refTipo = :v7, refContribuyente = :v8, refCuentaCompra = :v9, refAlicuota1 = :v10, netoGravado1 = :v11, refAlicuota2 = :v12, netoGravado2 = :v13, refAlicuota3 = :v14, netoGravado3 = :v15, refAlicuota4 = :v16, netoGravado4 = :v17, retencionesIVA = :v18, percepcionesIVA = :v19, retencionesIB = :v20, percepcionesIB = :v21, retencionesGanancias = :v22, conceptosNoGravados = :v23, exentos = :v24, total = :v25, refJurisdiccion = :v26  WHERE(idComprobanteCompra = :id)");
	  SQLQuery1->ParamByName("id")->AsInteger = idModificado;
   }


	  SQLQuery1->ParamByName("v1")->AsDate = StrToDate("01/" + EdPeriodo->Text);
	  SQLQuery1->ParamByName("v2")->AsDate = StrToDate(EdFecha->Text);
	  SQLQuery1->ParamByName("v3")->AsInteger = StrToInt(EdPtoVenta->Text);
	  SQLQuery1->ParamByName("v4")->AsInteger = StrToInt(EdNroComprobante->Text);
	  SQLQuery1->ParamByName("v5")->AsInteger = idProveedor;
	  SQLQuery1->ParamByName("v6")->AsInteger = StrToInt(EdDocumento->Text);
	  SQLQuery1->ParamByName("v7")->AsInteger = StrToInt(EdTipo->Text);
	  SQLQuery1->ParamByName("v8")->AsInteger = idContribuyente;
	  SQLQuery1->ParamByName("v9")->AsString = EdCuentaCompra->Text;

	  SQLQuery1->ParamByName("v10")->AsString = EdAlicuota1->Text;
	  SQLQuery1->ParamByName("v12")->AsString = EdAlicuota2->Text;
	  SQLQuery1->ParamByName("v14")->AsString = EdAlicuota3->Text;
	  SQLQuery1->ParamByName("v16")->AsString = EdAlicuota4->Text;

	  if(EdDocumento->Text != "3")
	  {
		 SQLQuery1->ParamByName("v11")->AsString = LimpiarNumero(EdNetoGravado1->Text);
		 SQLQuery1->ParamByName("v13")->AsString = LimpiarNumero(EdNetoGravado2->Text);
		 SQLQuery1->ParamByName("v15")->AsString = LimpiarNumero(EdNetoGravado3->Text);
		 SQLQuery1->ParamByName("v17")->AsString = LimpiarNumero(EdNetoGravado4->Text);

		 SQLQuery1->ParamByName("v18")->AsString = LimpiarNumero(EdRetencionesIVA->Text);
		 SQLQuery1->ParamByName("v19")->AsString = LimpiarNumero(EdPercepcionesIVA->Text);
		 SQLQuery1->ParamByName("v20")->AsString = LimpiarNumero(EdRetencionesIB->Text);
		 SQLQuery1->ParamByName("v21")->AsString = LimpiarNumero(EdPercepcionesIB->Text);
		 SQLQuery1->ParamByName("v22")->AsString = LimpiarNumero(EdRetencionesGanancias->Text);
		 SQLQuery1->ParamByName("v23")->AsString = LimpiarNumero(EdConcNoGravados->Text);
		 SQLQuery1->ParamByName("v24")->AsString = LimpiarNumero(EdExentos->Text);
		 SQLQuery1->ParamByName("v25")->AsString = LimpiarNumero(EdTotal->Text);
	  }
	  else
	  {
		 SQLQuery1->ParamByName("v11")->AsString = "-" + LimpiarNumero(EdNetoGravado1->Text);
		 SQLQuery1->ParamByName("v13")->AsString = "-" + LimpiarNumero(EdNetoGravado2->Text);
		 SQLQuery1->ParamByName("v15")->AsString = "-" + LimpiarNumero(EdNetoGravado3->Text);
		 SQLQuery1->ParamByName("v17")->AsString = "-" + LimpiarNumero(EdNetoGravado4->Text);

		 SQLQuery1->ParamByName("v18")->AsString = "-" + LimpiarNumero(EdRetencionesIVA->Text);
		 SQLQuery1->ParamByName("v19")->AsString = "-" + LimpiarNumero(EdPercepcionesIVA->Text);
		 SQLQuery1->ParamByName("v20")->AsString = "-" + LimpiarNumero(EdRetencionesIB->Text);
		 SQLQuery1->ParamByName("v21")->AsString = "-" + LimpiarNumero(EdPercepcionesIB->Text);
		 SQLQuery1->ParamByName("v22")->AsString = "-" + LimpiarNumero(EdRetencionesGanancias->Text);
		 SQLQuery1->ParamByName("v23")->AsString = "-" + LimpiarNumero(EdConcNoGravados->Text);
		 SQLQuery1->ParamByName("v24")->AsString = "-" + LimpiarNumero(EdExentos->Text);
		 SQLQuery1->ParamByName("v25")->AsString = "-" + LimpiarNumero(EdTotal->Text);
	  }

	  SQLQuery1->ParamByName("v26")->AsString = EdJurisdiccion->Text;


	  SQLQuery1->ExecSQL();

	  return true;
}
//---------------------------------------------------------------------------
void TCargarCompras::QuiereModificar(TObject *Sender)
{
   if(dynamic_cast <TEdit *>(Sender) != NULL)
   {
	  TEdit *Edit = dynamic_cast <TEdit *>(Sender);

	  int a = 0;
	  if(!modificando)
		 a = YaExiste();
	  if(a != 0)
	  {
		 if(Application->MessageBox(L"Este comprobante ya existe, desea modificarlo?",L"Comprobante existente!?",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES)
		 {
			TraerDatos(a);
			modificando = true;
			idModificado = a;
			CargarCompras->Caption = "*Modificando comprobante*";
			BtnAgregarComp->Caption = "Guardar cambios";
			BtnAgregarYCont->Caption = "Guardar y agregar otro";
			btEliminarComp->Enabled = true;
		 }
		 else
		 {
			if(Sender == EdDocumento || Sender == EdTipo)
			{
			   Edit->Text = "";
			   Edit->SetFocus();
			}
			else if(Sender == EdProveedor)
			{
			   Edit->Text = "__-________-_";
			   Edit->SetFocus();
			}
			else if(Sender == EdNroComprobante)
			{
			   Edit->Text = "00000000";
			   Edit->SetFocus();
			}
			else if(Sender == EdPtoVenta)
			{
			   Edit->Text = "00000";
			   Edit->SetFocus();
			}
		 }
	  }
   }
}
//---------------------------------------------------------------------------



//***************************************************************************
//***************FIN DE DEFINICION DE FUNCIONES******************************
//***************************************************************************



//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::BtnAgregarCompClick(TObject *Sender)
{
   if(GuardarDatos())
   {
	  AnsiString s1 = EdContribuyente->Text;
	  AnsiString s2 = EdPeriodo->Text;

	  RestablecerFormulario();

	  EdContribuyente->Text = s1;
	  EdPeriodo->Text = s2;
	  VerificarDatos(EdContribuyente);
	  VerificarDatos(EdPeriodo);

	  EdFecha->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdFechaExit(TObject *Sender)
{
   VerificarDatos(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdFechaKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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

void __fastcall TCargarCompras::EdFechaKeyPress(TObject *Sender, System::WideChar &Key)

{
	  EdFecha->SelLength = 1;
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdFechaKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(EdFecha->SelStart == 2 || EdFecha->SelStart == 5)
	  EdFecha->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdFechaMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   if(EdFecha->SelStart == 2 || EdFecha->SelStart == 5)
	  EdFecha->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdPeriodoExit(TObject *Sender)
{
   VerificarDatos(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdPeriodoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

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

void __fastcall TCargarCompras::EdPeriodoKeyPress(TObject *Sender, System::WideChar &Key)

{
   EdPeriodo->SelLength = 1;
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdPeriodoKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(EdPeriodo->SelStart == 2)
	  EdPeriodo->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdPeriodoMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   if(EdPeriodo->SelStart == 2)
	  EdPeriodo->SelStart++;
}
//---------------------------------------------------------------------------


void __fastcall TCargarCompras::EdProveedorKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(Key == VK_BACK)
   {
	  Key = NULL;
	  EdProveedor->Text = "___-________-_";
	  EdProveedor->SelStart = 0;
   }
   else if(Key == VK_DELETE)
   {
	  Key = NULL;
	  EdProveedor->Text = "__-________-_";
	  EdProveedor->SelStart = 0;
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdContribuyenteKeyPress(TObject *Sender, System::WideChar &Key)

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

void __fastcall TCargarCompras::EdProveedorKeyPress(TObject *Sender, System::WideChar &Key)

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
	  EdProveedor->Text = AuxQuery->FieldByName("cuit")->AsString;
	  AuxQuery->Close();

	  if(EdProveedor->Text == "")
		 EdProveedor->Text = "__-________-_";

	  EdPtoVenta->SetFocus();
   }

   EdProveedor->SelLength = 1;
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdProveedorKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(EdProveedor->SelStart == 2 || EdProveedor->SelStart == 11)
	  EdProveedor->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdContribuyenteKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
   if(EdContribuyente->SelStart == 2 || EdContribuyente->SelStart == 11)
	  EdContribuyente->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdContribuyenteKeyDown(TObject *Sender, WORD &Key,
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

void __fastcall TCargarCompras::EdProveedorMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   if(EdProveedor->SelStart == 2 || EdProveedor->SelStart == 11)
	  EdProveedor->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdContribuyenteMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   if(EdContribuyente->SelStart == 2 || EdContribuyente->SelStart == 11)
	  EdContribuyente->SelStart++;
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdProveedorExit(TObject *Sender)
{
   VerificarDatos(Sender);
   QuiereModificar(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdCuentaCompraExit(TObject *Sender)
{
   VerificarDatos(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdDocumentoExit(TObject *Sender)
{
   VerificarDatos(Sender);
   QuiereModificar(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdTipoExit(TObject *Sender)
{
   VerificarDatos(Sender);
   QuiereModificar(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdExentosExit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNetoGravado1Exit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   CalcularIVA(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNetoGravado2Exit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   CalcularIVA(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNetoGravado3Exit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   CalcularIVA(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNetoGravado4Exit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   CalcularIVA(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdRetencionesIVAExit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdPercepcionesIVAExit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdRetencionesIBExit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdPercepcionesIBExit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdRetencionesGananciasExit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdConcNoGravadosExit(TObject *Sender)
{
   DarFormatoEdit(Sender);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNetoGravado1Enter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNetoGravado2Enter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNetoGravado3Enter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNetoGravado4Enter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdRetencionesIVAEnter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdPercepcionesIVAEnter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdRetencionesIBEnter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdPercepcionesIBEnter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdRetencionesGananciasEnter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdConcNoGravadosEnter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdExentosEnter(TObject *Sender)
{
   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNetoGravado1KeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNetoGravado2KeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNetoGravado3KeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNetoGravado4KeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdRetencionesIVAKeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdPercepcionesIVAKeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdRetencionesIBKeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdPercepcionesIBKeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdRetencionesGananciasKeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdConcNoGravadosKeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdExentosKeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdTotalKeyPress(TObject *Sender, System::WideChar &Key)

{
   DarFormatoEntrada(Key);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNetoGravado1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNetoGravado2MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNetoGravado3MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNetoGravado4MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdRetencionesIVAMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdPercepcionesIVAMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdRetencionesIBMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdPercepcionesIBMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdRetencionesGananciasMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdConcNoGravadosMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdExentosMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdTotalMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdContribuyenteExit(TObject *Sender)
{
   VerificarDatos(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdPtoVentaExit(TObject *Sender)
{
   VerificarDatos(Sender);
   QuiereModificar(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNroComprobanteExit(TObject *Sender)
{
   VerificarDatos(Sender);
   QuiereModificar(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdTotalEnter(TObject *Sender)
{
   if(EdTipo->Text != "2" && EdTipo->Text != "3")
      ShowMessage("Atención! Se va a modificar manualmente el total. Verifique que la acción sea correcta");

   LimpiarEdit(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::FormShow(TObject *Sender)
{
   RestablecerFormulario();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::BtnCancelarClick(TObject *Sender)
{
   if(Application->MessageBox(L"Se van a cancelar todos los cambios. Desea continuar?",L"Cancelar cambios?",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) == IDYES)
   {
	   RestablecerFormulario();
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::BtnAgregarYContClick(TObject *Sender)
{
   if(GuardarDatos())
   {
	  RestablecerFormularioCont();
	  EdFecha->SetFocus();
   }
}
//---------------------------------------------------------------------------


void __fastcall TCargarCompras::EdCuentaCompraKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
      Opciones->llamador = 1;
	  Opciones->ShowModal();
	  Key = NULL;
	  EdCuentaCompra->Text = IntToStr(Opciones->idRetorno);
	  EdDocumento->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdDocumentoKeyPress(TObject *Sender, System::WideChar &Key)

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

void __fastcall TCargarCompras::EdTipoKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
	  Opciones->llamador = 4;
	  Opciones->ShowModal();
	  Key = NULL;
	  EdTipo->Text = IntToStr(Opciones->idRetorno);
	  EdJurisdiccion->SetFocus();
   }
}
//---------------------------------------------------------------------------


void __fastcall TCargarCompras::EdTotalExit(TObject *Sender)
{
   DarFormatoEdit(Sender);

   if(EdTipo->Text == "2")
   {
	  float aux = StrToFloat(EdTotal->Text.SubString(3,EdTotal->Text.Length()-2));
	  float aux2 = aux / 1.21;
	  EdNetoGravado1->Text = FormatFloat("$ 0.#0", aux2);
	  LabIVA1->Caption = FormatFloat("$ 0.#0", aux2 * 0.21);
   }

   BtnAgregarComp->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::AgProveedorClick(TObject *Sender)
{
   if(!provOK)
   {
      ModificarCuentas->RG->ItemIndex = 1;

      AgregarContribuyente->idContribuyente = idContribuyente;
	  AgregarContribuyente->llamador = 2;
	  AgregarContribuyente->EdCUIT->Text = EdProveedor->Text;
	  AgregarContribuyente->ShowModal();

	  VerificarDatos(EdProveedor);

	  EdPtoVenta->SetFocus();
   }
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdAlicuota1Exit(TObject *Sender)
{
   VerificarDatos(Sender);
   CalcularIVA(EdNetoGravado1);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdAlicuota2Exit(TObject *Sender)
{
   VerificarDatos(Sender);
   CalcularIVA(EdNetoGravado2);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdAlicuota3Exit(TObject *Sender)
{
   VerificarDatos(Sender);
   CalcularIVA(EdNetoGravado3);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdAlicuota4Exit(TObject *Sender)
{
   VerificarDatos(Sender);
   CalcularIVA(EdNetoGravado4);
   ActualizarTotal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdCuentaCompraMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdDocumentoMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdTipoMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdPtoVentaMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdNroComprobanteMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdAlicuota1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdAlicuota2MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdAlicuota3MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdAlicuota4MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdJurisdiccionExit(TObject *Sender)
{
   VerificarDatos(Sender);

   if(EdTipo->Text == "2" || EdTipo->Text == "3")
      EdTotal->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdJurisdiccionMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
   SeleccionarTodo(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::EdJurisdiccionKeyPress(TObject *Sender, System::WideChar &Key)

{
   if(Key == 'b' || Key == 'B')
   {
	  Opciones->llamador = 5;
	  Opciones->ShowModal();
	  Key = NULL;
	  EdJurisdiccion->Text = IntToStr(Opciones->idRetorno);

	  EdNetoGravado1->SetFocus();
   }
}
//---------------------------------------------------------------------------





void __fastcall TCargarCompras::btEliminarCompClick(TObject *Sender)
{
   if(!modificando)
	  return;

   if(Application->MessageBox(L"Atención! Se va a eliminar el comprobante seleccionado.",L"Eliminar comprobante?",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
	  return;
   if(Application->MessageBox(L"Esta acción no puede deshacerse, realmente desea continuar?",L"Confirma eliminación?",MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2) != IDYES)
      return;

   AuxQuery->Close();
   AuxQuery->SQL->Clear();
   AuxQuery->SQL->Add("DELETE FROM comprobantescompras WHERE(idComprobanteCompra = :id)");
   AuxQuery->ParamByName("id")->AsInteger = idModificado;
   AuxQuery->ExecSQL();

   RestablecerFormulario();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::btMostrarCompClick(TObject *Sender)
{
   if (!contOK || !perOK)
      return;

   fMostrarComprobantes->periodo = EdPeriodo->Text;
   fMostrarComprobantes->idContribuyente = idContribuyente;
   fMostrarComprobantes->llamador = 1;
   fMostrarComprobantes->ShowModal();

   if(fMostrarComprobantes->retorno > 0)
   {
	  if(Application->MessageBox(L"Se van a reemplazar todos los datos por los del comprobante seleccionado, desea continuar?",L"Reemplazar datos?",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
	  return;

      AuxQuery->Close();
	  AuxQuery->SQL->Clear();
	  AuxQuery->SQL->Add("SELECT fechaComprobante, ptoVenta, nroComprobante, refProveedor, refDocumento, refTipo FROM comprobantesCompras WHERE(idComprobanteCompra = :v)");
	  AuxQuery->ParamByName("v")->AsInteger = fMostrarComprobantes->retorno;
	  AuxQuery->Open();

	  EdPtoVenta->Text = AuxQuery->FieldByName("ptoVenta")->AsString;
	  EdNroComprobante->Text = AuxQuery->FieldByName("nroComprobante")->AsString;
	  EdDocumento->Text = AuxQuery->FieldByName("refDocumento")->AsString;
	  EdTipo->Text = AuxQuery->FieldByName("refTipo")->AsString;
	  EdFecha->Text = AuxQuery->FieldByName("fechaComprobante")->AsString;
	  int id = AuxQuery->FieldByName("refProveedor")->AsInteger;

	  AuxQuery->Close();
	  AuxQuery->SQL->Clear();
	  AuxQuery->SQL->Add("SELECT cuit FROM Contribuyentes WHERE(idContribuyente = :v)");
	  AuxQuery->ParamByName("v")->AsInteger = id;
	  AuxQuery->Open();
	  EdProveedor->Text = AuxQuery->FieldByName("cuit")->AsString;
	  AuxQuery->Close();


	  VerificarDatos(EdPtoVenta);
	  VerificarDatos(EdNroComprobante);
	  VerificarDatos(EdDocumento);
	  VerificarDatos(EdTipo);
	  VerificarDatos(EdProveedor);


	  TraerDatos(fMostrarComprobantes->retorno);
	  modificando = true;
	  idModificado = fMostrarComprobantes->retorno;
	  CargarCompras->Caption = "*Modificando comprobante*";
	  BtnAgregarComp->Caption = "Guardar cambios";
	  BtnAgregarYCont->Caption = "Guardar cambios y agregar otro";
	  btEliminarComp->Enabled = true;
   }

}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::BtnCancelarExit(TObject *Sender)
{
   if(!btEliminarComp->Enabled)
	  BtnAgregarComp->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::btEliminarCompExit(TObject *Sender)
{
   BtnAgregarComp->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TCargarCompras::SpeedButton1Click(TObject *Sender)
{
   ModificarCuentas->RG->ItemIndex = 1;
   ModificarCuentas->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TCargarCompras::Edit1Exit(TObject *Sender)
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

void __fastcall TCargarCompras::Edit2Exit(TObject *Sender)
{
   if(Edit2->Text != "")
   {
       AuxQuery->Close();
	   AuxQuery->SQL->Clear();
	   AuxQuery->SQL->Add("SELECT cuit FROM Contribuyentes WHERE(idContribuyente = :v)");
	   AuxQuery->ParamByName("v")->AsString= Edit2->Text;
	   AuxQuery->Open();
	   EdProveedor->Text = AuxQuery->FieldByName("cuit")->AsString;
	   AuxQuery->Close();

	   if(EdProveedor->Text == "")
		 EdProveedor->Text = "__-________-_";
   }
   EdProveedor->SetFocus();
   Edit2->Clear();
}
//---------------------------------------------------------------------------


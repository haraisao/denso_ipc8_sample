/*
 *
 */
#include "rc8server.h"

void
print_variant(VARIANT *vnt, int depth)
{
#ifdef _MSC_VER
  LONG i, lb, ub;
  char chTab[128];
#else
  int32_t i, lb, ub;
  char chTab[128], chTmp[128];
#endif
  void *pData;
  VARIANT vntTmp, vntDate;
  VariantInit(&vntTmp);
  VariantInit(&vntDate);

  for (i = 0; i < depth; i++) {
    chTab[i] = '\t';
  }
  chTab[i] = '\0';

  printf("%svt: %d\n", chTab, vnt->vt);
  printf("%sdata: ", chTab);

  if (vnt->vt & VT_ARRAY) {
    SafeArrayGetLBound(vnt->parray, 1, &lb);
    SafeArrayGetUBound(vnt->parray, 1, &ub);

    SafeArrayAccessData(vnt->parray, &pData);

    printf("%s", chTab);

    switch (vnt->vt & ~VT_ARRAY) {
      case VT_I2:
        for (i = 0; i <= (ub - lb); i++) {
          printf("%d", *((int16_t *) pData + i));
          if (i != (ub - lb))
            printf(", ");
        }
        break;
      case VT_I4:
        for (i = 0; i <= (ub - lb); i++) {
          printf("%d", *((int32_t *) pData + i));
          if (i != (ub - lb))
            printf(", ");
        }
        break;
      case VT_R4:
        for (i = 0; i <= (ub - lb); i++) {
          printf("%f", *((float *) pData + i));
          if (i != (ub - lb))
            printf(", ");
        }
        break;
      case VT_R8:
        for (i = 0; i <= (ub - lb); i++) {
          printf("%lf", *((double *) pData + i));
          if (i != (ub - lb))
            printf(", ");
        }
        break;
      case VT_CY:
        for (i = 0; i <= (ub - lb); i++) {
          printf("%lld", ((CY *) pData + i)->int64);
          if (i != (ub - lb))
            printf(", ");
        }
        break;
      case VT_DATE:
        vntDate.vt = VT_DATE;
        for (i = 0; i <= (ub - lb); i++) {
          vntDate.date = *((DATE *) pData + i);
#ifdef _MSC_VER
          VariantChangeType(&vntTmp, &vntDate, 0, VT_BSTR);
          printf("%ls", vntTmp.bstrVal);
          VariantClear(&vntTmp);
#else
          strftime(chTmp, 128, "%Y-%m-%d %H:%M:%S",
              gmtime((DATE *) pData + i));
          printf("%s", chTmp);
#endif
          if (i != (ub - lb))
            printf(", ");
        }
        break;
      case VT_BSTR:
        for (i = 0; i <= (ub - lb); i++) {
          printf("%ls", *((BSTR *) pData + i));
          if (i != (ub - lb))
            printf(", ");
        }
        break;
      case VT_ERROR:
        for (i = 0; i <= (ub - lb); i++) {
          printf("%08X", *((int32_t *) pData + i));
          if (i != (ub - lb))
            printf(", ");
        }
        break;
      case VT_BOOL:
        for (i = 0; i <= (ub - lb); i++) {
          printf("%s",
              (*((VARIANT_BOOL *) pData + i) == VARIANT_TRUE) ?
                  "true" : "false");
          if (i != (ub - lb))
            printf(", ");
        }
        break;
      case VT_VARIANT:
        printf("\n");
        for (i = 0; i <= (ub - lb); i++) {
          print_variant(((VARIANT *) pData + i), depth + 1);
        }
        break;
      case VT_UI1:
        for (i = 0; i <= (ub - lb); i++) {
          printf("%u", *((uint8_t *) pData + i));
          if (i != (ub - lb))
            printf(", ");
        }
        break;
      case VT_UI2:
        for (i = 0; i <= (ub - lb); i++) {
          printf("%u", *((uint16_t *) pData + i));
          if (i != (ub - lb))
            printf(", ");
        }
        break;
      case VT_UI4:
        for (i = 0; i <= (ub - lb); i++) {
          printf("%u", *((uint32_t *) pData + i));
          if (i != (ub - lb))
            printf(", ");
        }
        break;
    }

    printf("\n");

    SafeArrayUnaccessData(vnt->parray);
  } else {
    switch (vnt->vt) {
      case VT_I2:
        printf("%d", vnt->iVal);
        break;
      case VT_I4:
        printf("%d", vnt->lVal);
        break;
      case VT_R4:
        printf("%f", vnt->fltVal);
        break;
      case VT_R8:
        printf("%lf", vnt->dblVal);
        break;
      case VT_CY:
        printf("%lld", vnt->cyVal.int64);
        break;
      case VT_DATE:
#ifdef _MSC_VER
        VariantChangeType(&vntTmp, vnt, 0, VT_BSTR);
        printf("%ls", vntTmp.bstrVal);
        VariantClear(&vntTmp);
#else
        strftime(chTmp, 128, "%Y-%m-%d %H:%M:%S", gmtime(&vnt->date));
        printf("%s", chTmp);
#endif
        break;
      case VT_BSTR:
        printf("%ls", vnt->bstrVal);
        break;
      case VT_ERROR:
        printf("%08X", vnt->scode);
        break;
      case VT_BOOL:
        printf("%s", (vnt->boolVal == VARIANT_TRUE) ? "true" : "false");
        break;
      case VT_UI1:
        printf("%u", vnt->bVal);
        break;
      case VT_UI2:
        printf("%u", vnt->uiVal);
        break;
      case VT_UI4:
        printf("%u", vnt->ulVal);
        break;
      default:
        printf("(nil)");
        break;
    }

    printf("\n");
  }
}

void
print_args(const char *chName, VARIANT *vntArgs, int16_t Argc)
{
#if 0
  int16_t i;
  printf("%s\n", chName);
  for (i = 0; i < Argc; i++) {
    printf("Arg[%d]\n", i + 1);
    print_variant(&vntArgs[i], 1);
  }
  printf("\n");
#else
  //printf("%s\n", chName);
  return;
#endif
}

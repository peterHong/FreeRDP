/*
 * Generated by asn1c-0.9.22.1409 (http://lionet.info/asn1c)
 * From ASN.1 module "MCS-PROTOCOL-3"
 * 	found in "mcs.asn1"
 * 	`asn1c -fnative-types -fskeletons-copy -fcompound-names -gen-PER`
 */

#ifndef	_ExtendedParameterMCSPDU_H_
#define	_ExtendedParameterMCSPDU_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ExtendedParameterPropose.h"
#include "ExtendedParameterAccept.h"
#include "NonStandardPDU.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ExtendedParameterMCSPDU_PR {
	ExtendedParameterMCSPDU_PR_NOTHING,	/* No components present */
	ExtendedParameterMCSPDU_PR_extendedParameterPropose,
	ExtendedParameterMCSPDU_PR_extendedParameterAccept,
	ExtendedParameterMCSPDU_PR_nonStandard,
	/* Extensions may appear below */
	
} ExtendedParameterMCSPDU_PR;

/* ExtendedParameterMCSPDU */
typedef struct ExtendedParameterMCSPDU {
	ExtendedParameterMCSPDU_PR present;
	union ExtendedParameterMCSPDU_u {
		ExtendedParameterPropose_t	 extendedParameterPropose;
		ExtendedParameterAccept_t	 extendedParameterAccept;
		NonStandardPDU_t	 nonStandard;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ExtendedParameterMCSPDU_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ExtendedParameterMCSPDU;

#ifdef __cplusplus
}
#endif

#endif	/* _ExtendedParameterMCSPDU_H_ */
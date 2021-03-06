/*
   FreeRDP: A Remote Desktop Protocol client.
   FreeRDP Unit Tests

   Copyright 2010 Marc-Andre Moreau <marcandre.moreau@gmail.com>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "CUnit/Basic.h"

#include "test_credssp.h"
#include "test_ntlmssp.h"
#include "test_libgdi.h"
#include "test_gdi_color.h"
#include "test_freerdp.h"

void dump_data(unsigned char * p, int len, int width, char* name)
{
	unsigned char *line = p;
	int i, thisline, offset = 0;

	printf("\n%s[%d][%d]:\n", name, len / width, width);
	while (offset < len)
	{
		printf("%04x ", offset);
		thisline = len - offset;
		if (thisline > width)
			thisline = width;

		for (i = 0; i < thisline; i++)
			printf("%02x ", line[i]);

		for (; i < width; i++)
			printf("   ");

		printf("\n");
		offset += thisline;
		line += thisline;
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	if (CU_initialize_registry() != CUE_SUCCESS)
		return CU_get_error();

	//add_credssp_suite();
	//add_ntlmssp_suite();
	add_libgdi_suite();

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}


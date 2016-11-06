#pragma once
#include <string.h>

void DEL()
{
  while (getchar() != '\n');
}

void strtrim(char *s)
{
  int i, j;
  char st[500];
  i = j = 1;
  if (s[0] == ' ') j = 0;
  else  st[0] = s[0];
  while (s[i] != '\0')
    {
      if (s[i] == ' ' && s[i-1] == ' ') 
	{
	  i++;
	  continue;
	}
      st[j] = s[i];
      j++;
      i++;
    }
  if (st[j-1] == ' ') j--;
  for (i=0; i<j; i++)
    {
      s[i] = st[i];
    }
  s[j] = '\0';
}

void vietHoaTen(char *s)
{
  int i = 0;
  while (s[i] != '\0')
    {
      if ((i == 0 || s[i-1] == ' ') && s[i] >= 'a' && s[i] <= 'z') 
	{ 
	  s[i] = s[i] + 'A' - 'a';
	}
      if (i!=0 && s[i-1] != ' ' && s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a';
      i++;
    }
}

char *strsub(char *s, int offset, int number)
{
  int len;
  len = strlen(s);
  int i, j;
  char *ssub;
  if (offset < 0 || offset >= len)
    {
      printf("Vi tri offset sai\n");
      exit(0);
    }
  if (number < 0)
    {
      printf("Do dai xau moi phai >= 0\n");
      exit(0);
    }
  if (number + offset <= len)
    {
      ssub = (char*)malloc(number*sizeof(char));
      for (i=offset, j=0; j<number; i++, j++)
	ssub[j] = s[i];
      ssub[j] = '\0';
    }
  else
    {
      ssub = (char *)malloc((len-offset)*sizeof(char));
      if (ssub == NULL)
	{
	  printf("Khong cap phat duoc bo nho\n");
	  return 0;
	}
      for (i=offset, j=0; i<len; i++, j++)
	ssub[j] = s[i];
      ssub[j] = '\0';
    }
  return ssub;
}

void strlwr(char *s2, char* s)
{
  int i = 0;
  while (s[i] != '\0')
    {
      if (s[i] >= 'A' && s[i] <= 'Z') s2[i] = s[i] + 'a' - 'A';
      else s2[i] = s[i];
      i++;
    }
  s2[i] = '\0';
}

int strcmpnamevi(char *s1, char *s2) //So sanh ten Viet Nam
{
  int len1, len2, i, p1, p2, j;
  char v1[80], v2[80];
  len1 = strlen(s1);
  len2 = strlen(s2);
  for (i=0; i<len1; i++)
    if (s1[i] == ' ') break;
  p1 = i;
  for (i=len1-1; i>=0; i--) if (s1[i] == ' ') break;
  p2 = i;
  j = 0;
  for (i=p2+1; i<len1; i++, j++) v1[j] = s1[i];
  for (i=p1; i<=p2; i++, j++) v1[j] = s1[i];
  for (i=0; i<p1; i++, j++) v1[j] = s1[i];
  v1[j] = '\0';

  for (i=0; i<len2; i++)
    if (s2[i] == ' ') break;
  p1 = i;
  for (i=len2-1; i>=0; i--) if (s2[i] == ' ') break;
  p2 = i;
  j = 0;
  for (i=p2+1; i<len2; i++, j++) v2[j] = s2[i];
  for (i=p1; i<=p2; i++, j++) v2[j] = s2[i];
  for (i=0; i<p1; i++, j++) v2[j] = s2[i];
  v2[j] = '\0';

  return strcmp(v1,v2);
}

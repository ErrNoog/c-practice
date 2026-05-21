#include <stdio.h>
#include <stdlib.h>
 
#define BACK_TO_BEGIN_THE_WORD while(tar->prev) tar = tar->prev;

typedef struct node {
		int data;
		struct node *next, *prev;
	} item;

item *c_a(item *first, item **last, int c)
{
	item *tmp;
	tmp = malloc(sizeof(*tmp));
	tmp->data = c;
	tmp->next = NULL;
	if(!first) {
		first = tmp;
		tmp->prev = NULL;
	} else {
		tmp->prev = *last;
		(*last)->next = tmp;
	}
	*last = tmp;
	return first;
}

item *insert_arr(item *arr)
{
	item *tmp;
	tmp = malloc(sizeof(*tmp));
	tmp->data = ' ';
	tmp->prev = arr->prev;
	tmp->next = arr;
	arr->prev = tmp;
	tmp->prev->next = tmp;
	return arr;
}

item *delete_arr(item *arr)
{
	while(arr) {
		item *tmp = arr;
		arr = arr->next;
		free(tmp);
	}
    return arr;
}

item *del(item *arr)
{
    item *tmp = arr;
    if(arr->next) {
		arr = arr->next;
		free(tmp);
	}
    return arr;
}

void showarr(item *arr)
{
	while(arr) {
		printf("%c", arr->data);
		arr = arr->next;
	}
}

item *get_word(item *arr)
{
    item *word = NULL, *last = NULL;
    /* create first word */
	while(arr->data != ' ') {
		word = c_a(word, &last, arr->data);
		arr = arr->next;
	}
    return word;
}

item *get_long_word(item *arr)
{

    item *tar = NULL, *last = NULL;
    tar = get_word(arr);
	while(arr->next) {
		arr = arr->next;
		if(arr->data != ' ' && !tar->next) {
		   	BACK_TO_BEGIN_THE_WORD
            while(arr->prev->data != ' ') 
				arr = arr->prev;
		   	tar = delete_arr(tar);
		   	/* create long word */
			while(arr->data != ' ' && 
					arr->next) {
			    tar = c_a(tar, &last, 
			    		arr->data);
			    arr = arr->next;
			}
		}
		if(arr->data == ' ') {
		   	BACK_TO_BEGIN_THE_WORD
		    arr = arr->next;
        } else 
            tar = tar->next;
	}
    if(tar) {
        BACK_TO_BEGIN_THE_WORD
    }
	return tar;
}


item *ins(item *arr, item *wrd)
{
	item *bega = arr, *begw = wrd;
	while(arr) {
		if((!arr->next || arr->data == ' ')
			&& wrd) {
			if(!arr->next)
				arr = insert_arr(arr);
			while(wrd) {
				arr = insert_arr(arr);
				wrd = wrd->next;
			}
			wrd = begw;
		} else {
			if(!wrd)
				wrd = begw;
			else
				wrd = wrd->next;
		}
		arr = arr->next;
	}
	arr = bega;
	return arr;
}

item *vert(item *arr, item **wrd)
{
	item *fr = NULL, *ls = NULL;
	item *s_wrd = *wrd, *s_arr = arr;
	item *temp_wrd = *wrd;
	while(temp_wrd) {
		while(arr) {
			if(arr->data != '\n')
			    fr = c_a(fr, &ls, arr->data);
			while(*wrd && arr->next) {
				arr = arr->next;
				*wrd = (*wrd)->next;
			}
			*wrd = s_wrd;
			arr = arr->next;
		}
        showarr(fr);
		printf("\n");
	    fr = delete_arr(fr);
		arr = s_arr;
		arr = del(arr);	
		s_arr = arr;
		temp_wrd = temp_wrd->next;
	}
    return s_arr;
}

int main()
{
	item *first = NULL, *last = NULL, *word = NULL;
	int c = 0;
    while((c = getchar()) != EOF) {
		first = c_a(first, &last, c);
	    while((c = getchar()) != '\n') {
		    first = c_a(first, &last, c);
	    }
		first = c_a(first, &last, c);
        if(first->data != '\n') {
	        word = get_long_word(first);
	        first = ins(first, word);
	        first = vert(first, &word);
        }
        word = delete_arr(word);
        first = delete_arr(first);
        c = 'a';
    }
	return 0;
}

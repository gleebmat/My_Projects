
import {Fragment,memo,useCallback,useEffect} from "react"
import {ReflexEvent,applyEventActions,getRefValue,getRefValues,isTrue} from "$/utils/state"
import {Root as RadixFormRoot} from "@radix-ui/react-form"
import {addEvents} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Form_root_2c3bf866be42a94936f171cc0bf0348e = memo(({children}) => {
    

    const handleSubmit_58c5c5d00b7ec4d8640c136699ac4859 = useCallback((ev) => {
        const $form = ev.target
        ev.preventDefault()
        const form_data = {...Object.fromEntries(new FormData($form).entries()), ...({  })};

        (((...args) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.register", ({ ["form_data"] : form_data }), ({  })))], args, ({  }))))(ev));

        if (false) {
            $form.reset()
        }
    })
    


    return(
        jsx(RadixFormRoot,{className:"Root ",css:({ ["width"] : "100%" }),onSubmit:handleSubmit_58c5c5d00b7ec4d8640c136699ac4859},children)
    )
});
